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
  build() {
    Scroll() {
      Flex({ wrap: FlexWrap.Wrap, justifyContent: FlexAlign.SpaceBetween, alignItems: ItemAlign.Center }) {
        for (let i = 0; i < forEachItems20.length; i++) {
          ParallelizeUI({} as ParallelOption) {
            ForEach(forEachItems100,(item: Int, index: Double)=>{
              {
                Column(undefined) {
                  Text('image').fontSize(40)
                  Text('fillColor: Blue & syncLoad').fontSize(14)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .fillColor(Color.Blue)
                      .syncLoad(true)
                      .width(80)
                      .height(80)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.startIcon'))
                      .fillColor(undefined)
                      .syncLoad(undefined)
                      .width(80)
                      .height(80)
                      .border({ width: 1, color: Color.Black })
                  }
                  Text('---------------------------').fontSize(14)
                  Text('fitOriginalSize').fontSize(22).margin({ bottom: 15 } as Margin)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .fitOriginalSize(undefined)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.startIcon'))
                      .fitOriginalSize(true)
                      .border({ width: 1, color: Color.Black })
                  }
                  Text('---------------------------').fontSize(14)
                  Text('sourceSize').fontSize(22).margin({ bottom: 15 } as Margin)
                  
                  Row() {
                    Image($r('app.media.no8'))
                      .sourceSize({ width: 100, height: 100 })
                      .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.no8'))
                      .sourceSize(undefined)
                       .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                    }
                  Text('---------------------------').fontSize(14)
                  
                  Text('small & enableAnalyzer').fontSize(14)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .sourceSize({ width: 50, height: 50 })
                      .enableAnalyzer(true)
                      .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.startIcon'))
                      .sourceSize(undefined)
                      .enableAnalyzer(undefined)
                      .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                  }
                  Text('---------------------------').fontSize(14)
                  
                  Text('dynamicRangeMode').fontSize(22).margin({ bottom: 15 } as Margin)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .dynamicRangeMode(DynamicRangeMode.STANDARD)
                      .width(150)
                      .height(150)
                      .border({ width: 2, color: Color.Blue })
                    Image($r('app.media.startIcon'))
                      .dynamicRangeMode(undefined)
                      .width(150)
                      .height(150)
                      .border({ width: 2, color: Color.Blue })
                  }
                  Text('---------------------------').fontSize(14)
                }
              }
            })
          }
          ParallelizeUI({} as ParallelOption) {
            ForEach(forEachItems100,(item: Int, index: Double)=>{
              {
                Column(undefined) {
                  Text('image').fontSize(40)
                  Text('fillColor: Blue & syncLoad').fontSize(14)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .fillColor(Color.Blue)
                      .syncLoad(true)
                      .width(80)
                      .height(80)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.startIcon'))
                      .fillColor(undefined)
                      .syncLoad(undefined)
                      .width(80)
                      .height(80)
                      .border({ width: 1, color: Color.Black })
                  }
                  Text('---------------------------').fontSize(14)
                  Text('fitOriginalSize').fontSize(22).margin({ bottom: 15 } as Margin)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .fitOriginalSize(undefined)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.startIcon'))
                      .fitOriginalSize(true)
                      .border({ width: 1, color: Color.Black })
                  }
                  Text('---------------------------').fontSize(14)
                  Text('sourceSize').fontSize(22).margin({ bottom: 15 } as Margin)
                  
                  Row() {
                    Image($r('app.media.no8'))
                      .sourceSize({ width: 100, height: 100 })
                      .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.no8'))
                      .sourceSize(undefined)
                       .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                    }
                  Text('---------------------------').fontSize(14)
                  
                  Text('small & enableAnalyzer').fontSize(14)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .sourceSize({ width: 50, height: 50 })
                      .enableAnalyzer(true)
                      .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.startIcon'))
                      .sourceSize(undefined)
                      .enableAnalyzer(undefined)
                      .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                  }
                  Text('---------------------------').fontSize(14)
                  
                  Text('dynamicRangeMode').fontSize(22).margin({ bottom: 15 } as Margin)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .dynamicRangeMode(DynamicRangeMode.STANDARD)
                      .width(150)
                      .height(150)
                      .border({ width: 2, color: Color.Blue })
                    Image($r('app.media.startIcon'))
                      .dynamicRangeMode(undefined)
                      .width(150)
                      .height(150)
                      .border({ width: 2, color: Color.Blue })
                  }
                  Text('---------------------------').fontSize(14)
                }
              }
            })
          }
          ParallelizeUI({} as ParallelOption) {
            ForEach(forEachItems100,(item: Int, index: Double)=>{
              {
                Column(undefined) {
                  Text('image').fontSize(40)
                  Text('fillColor: Blue & syncLoad').fontSize(14)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .fillColor(Color.Blue)
                      .syncLoad(true)
                      .width(80)
                      .height(80)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.startIcon'))
                      .fillColor(undefined)
                      .syncLoad(undefined)
                      .width(80)
                      .height(80)
                      .border({ width: 1, color: Color.Black })
                  }
                  Text('---------------------------').fontSize(14)
                  Text('fitOriginalSize').fontSize(22).margin({ bottom: 15 } as Margin)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .fitOriginalSize(undefined)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.startIcon'))
                      .fitOriginalSize(true)
                      .border({ width: 1, color: Color.Black })
                  }
                  Text('---------------------------').fontSize(14)
                  Text('sourceSize').fontSize(22).margin({ bottom: 15 } as Margin)
                  
                  Row() {
                    Image($r('app.media.no8'))
                      .sourceSize({ width: 100, height: 100 })
                      .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.no8'))
                      .sourceSize(undefined)
                       .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                  }
                  Text('---------------------------').fontSize(14)
                  
                  Text('small & enableAnalyzer').fontSize(14)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .sourceSize({ width: 50, height: 50 })
                      .enableAnalyzer(true)
                      .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.startIcon'))
                      .sourceSize(undefined)
                      .enableAnalyzer(undefined)
                      .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                  }
                  Text('---------------------------').fontSize(14)
                  
                  Text('dynamicRangeMode').fontSize(22).margin({ bottom: 15 } as Margin)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .dynamicRangeMode(DynamicRangeMode.STANDARD)
                      .width(150)
                      .height(150)
                      .border({ width: 2, color: Color.Blue })
                    Image($r('app.media.startIcon'))
                      .dynamicRangeMode(undefined)
                      .width(150)
                      .height(150)
                      .border({ width: 2, color: Color.Blue })
                  }
                  Text('---------------------------').fontSize(14)
                }
              }
            })
          }
          ParallelizeUI({} as ParallelOption) {
            ForEach(forEachItems100,(item: Int, index: Double)=>{
              {
                Column(undefined) {
                  Text('image').fontSize(40)
                  Text('fillColor: Blue & syncLoad').fontSize(14)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .fillColor(Color.Blue)
                      .syncLoad(true)
                      .width(80)
                      .height(80)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.startIcon'))
                      .fillColor(undefined)
                      .syncLoad(undefined)
                      .width(80)
                      .height(80)
                      .border({ width: 1, color: Color.Black })
                  }
                  Text('---------------------------').fontSize(14)
                  Text('fitOriginalSize').fontSize(22).margin({ bottom: 15 } as Margin)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .fitOriginalSize(undefined)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.startIcon'))
                      .fitOriginalSize(true)
                      .border({ width: 1, color: Color.Black })
                  }
                  Text('---------------------------').fontSize(14)
                  Text('sourceSize').fontSize(22).margin({ bottom: 15 } as Margin)
                  
                  Row() {
                    Image($r('app.media.no8'))
                      .sourceSize({ width: 100, height: 100 })
                      .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.no8'))
                      .sourceSize(undefined)
                      .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                    }
                  Text('---------------------------').fontSize(14)
                  
                  Text('small & enableAnalyzer').fontSize(14)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .sourceSize({ width: 50, height: 50 })
                      .enableAnalyzer(true)
                      .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.startIcon'))
                      .sourceSize(undefined)
                      .enableAnalyzer(undefined)
                      .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                  }
                  Text('---------------------------').fontSize(14)
                  
                  Text('dynamicRangeMode').fontSize(22).margin({ bottom: 15 } as Margin)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .dynamicRangeMode(DynamicRangeMode.STANDARD)
                      .width(150)
                      .height(150)
                      .border({ width: 2, color: Color.Blue })
                    Image($r('app.media.startIcon'))
                      .dynamicRangeMode(undefined)
                      .width(150)
                      .height(150)
                      .border({ width: 2, color: Color.Blue })
                  }
                  Text('---------------------------').fontSize(14)
                }
              }
            })
          }
          ParallelizeUI({} as ParallelOption) {
            ForEach(forEachItems100,(item: Int, index: Double)=>{
              {
                Column(undefined) {
                  Text('image').fontSize(40)
                  Text('fillColor: Blue & syncLoad').fontSize(14)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .fillColor(Color.Blue)
                      .syncLoad(true)
                      .width(80)
                      .height(80)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.startIcon'))
                      .fillColor(undefined)
                      .syncLoad(undefined)
                      .width(80)
                      .height(80)
                      .border({ width: 1, color: Color.Black })
                  }
                  Text('---------------------------').fontSize(14)
                  Text('fitOriginalSize').fontSize(22).margin({ bottom: 15 } as Margin)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .fitOriginalSize(undefined)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.startIcon'))
                      .fitOriginalSize(true)
                      .border({ width: 1, color: Color.Black })
                  }
                  Text('---------------------------').fontSize(14)
                  Text('sourceSize').fontSize(22).margin({ bottom: 15 } as Margin)
                  
                  Row() {
                    Image($r('app.media.no8'))
                      .sourceSize({ width: 100, height: 100 })
                      .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.no8'))
                      .sourceSize(undefined)
                       .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                    }
                  Text('---------------------------').fontSize(14)
                  
                  Text('small & enableAnalyzer').fontSize(14)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .sourceSize({ width: 50, height: 50 })
                      .enableAnalyzer(true)
                      .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.startIcon'))
                      .sourceSize(undefined)
                      .enableAnalyzer(undefined)
                      .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                  }
                  Text('---------------------------').fontSize(14)
                  
                  Text('dynamicRangeMode').fontSize(22).margin({ bottom: 15 } as Margin)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .dynamicRangeMode(DynamicRangeMode.STANDARD)
                      .width(150)
                      .height(150)
                      .border({ width: 2, color: Color.Blue })
                    Image($r('app.media.startIcon'))
                      .dynamicRangeMode(undefined)
                      .width(150)
                      .height(150)
                      .border({ width: 2, color: Color.Blue })
                  }
                  Text('---------------------------').fontSize(14)
                }
              }
            })
          }
          ParallelizeUI({} as ParallelOption) {
            ForEach(forEachItems100,(item: Int, index: Double)=>{
              {
                Column(undefined) {
                  Text('image').fontSize(40)
                  Text('fillColor: Blue & syncLoad').fontSize(14)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .fillColor(Color.Blue)
                      .syncLoad(true)
                      .width(80)
                      .height(80)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.startIcon'))
                      .fillColor(undefined)
                      .syncLoad(undefined)
                      .width(80)
                      .height(80)
                      .border({ width: 1, color: Color.Black })
                  }
                  Text('---------------------------').fontSize(14)
                  Text('fitOriginalSize').fontSize(22).margin({ bottom: 15 } as Margin)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .fitOriginalSize(undefined)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.startIcon'))
                      .fitOriginalSize(true)
                      .border({ width: 1, color: Color.Black })
                  }
                  Text('---------------------------').fontSize(14)
                  Text('sourceSize').fontSize(22).margin({ bottom: 15 } as Margin)
                  
                  Row() {
                    Image($r('app.media.no8'))
                      .sourceSize({ width: 100, height: 100 })
                      .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.no8'))
                      .sourceSize(undefined)
                       .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                    }
                  Text('---------------------------').fontSize(14)
                  
                  Text('small & enableAnalyzer').fontSize(14)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .sourceSize({ width: 50, height: 50 })
                      .enableAnalyzer(true)
                      .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.startIcon'))
                      .sourceSize(undefined)
                      .enableAnalyzer(undefined)
                      .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                  }
                  Text('---------------------------').fontSize(14)
                  
                  Text('dynamicRangeMode').fontSize(22).margin({ bottom: 15 } as Margin)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .dynamicRangeMode(DynamicRangeMode.STANDARD)
                      .width(150)
                      .height(150)
                      .border({ width: 2, color: Color.Blue })
                    Image($r('app.media.startIcon'))
                      .dynamicRangeMode(undefined)
                      .width(150)
                      .height(150)
                      .border({ width: 2, color: Color.Blue })
                  }
                  Text('---------------------------').fontSize(14)
                }
              }
            })
          }
          ParallelizeUI({} as ParallelOption) {
            ForEach(forEachItems100,(item: Int, index: Double)=>{
              {
                Column(undefined) {
                  Text('image').fontSize(40)
                  Text('fillColor: Blue & syncLoad').fontSize(14)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .fillColor(Color.Blue)
                      .syncLoad(true)
                      .width(80)
                      .height(80)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.startIcon'))
                      .fillColor(undefined)
                      .syncLoad(undefined)
                      .width(80)
                      .height(80)
                      .border({ width: 1, color: Color.Black })
                  }
                  Text('---------------------------').fontSize(14)
                  Text('fitOriginalSize').fontSize(22).margin({ bottom: 15 } as Margin)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .fitOriginalSize(undefined)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.startIcon'))
                      .fitOriginalSize(true)
                      .border({ width: 1, color: Color.Black })
                  }
                  Text('---------------------------').fontSize(14)
                  Text('sourceSize').fontSize(22).margin({ bottom: 15 } as Margin)
                  
                  Row() {
                    Image($r('app.media.no8'))
                      .sourceSize({ width: 100, height: 100 })
                      .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.no8'))
                      .sourceSize(undefined)
                       .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                    }
                  Text('---------------------------').fontSize(14)
                  
                  Text('small & enableAnalyzer').fontSize(14)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .sourceSize({ width: 50, height: 50 })
                      .enableAnalyzer(true)
                      .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.startIcon'))
                      .sourceSize(undefined)
                      .enableAnalyzer(undefined)
                      .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                  }
                  Text('---------------------------').fontSize(14)
                  
                  Text('dynamicRangeMode').fontSize(22).margin({ bottom: 15 } as Margin)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .dynamicRangeMode(DynamicRangeMode.STANDARD)
                      .width(150)
                      .height(150)
                      .border({ width: 2, color: Color.Blue })
                    Image($r('app.media.startIcon'))
                      .dynamicRangeMode(undefined)
                      .width(150)
                      .height(150)
                      .border({ width: 2, color: Color.Blue })
                  }
                  Text('---------------------------').fontSize(14)
                }
              }
            })
          }
          ParallelizeUI({} as ParallelOption) {
            ForEach(forEachItems100,(item: Int, index: Double)=>{
              {
                Column(undefined) {
                  Text('image').fontSize(40)
                  Text('fillColor: Blue & syncLoad').fontSize(14)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .fillColor(Color.Blue)
                      .syncLoad(true)
                      .width(80)
                      .height(80)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.startIcon'))
                      .fillColor(undefined)
                      .syncLoad(undefined)
                      .width(80)
                      .height(80)
                      .border({ width: 1, color: Color.Black })
                  }
                  Text('---------------------------').fontSize(14)
                  Text('fitOriginalSize').fontSize(22).margin({ bottom: 15 } as Margin)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .fitOriginalSize(undefined)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.startIcon'))
                      .fitOriginalSize(true)
                      .border({ width: 1, color: Color.Black })
                  }
                  Text('---------------------------').fontSize(14)
                  Text('sourceSize').fontSize(22).margin({ bottom: 15 } as Margin)
                  
                  Row() {
                    Image($r('app.media.no8'))
                      .sourceSize({ width: 100, height: 100 })
                      .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.no8'))
                      .sourceSize(undefined)
                       .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                    }
                  Text('---------------------------').fontSize(14)
                  
                  Text('small & enableAnalyzer').fontSize(14)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .sourceSize({ width: 50, height: 50 })
                      .enableAnalyzer(true)
                      .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.startIcon'))
                      .sourceSize(undefined)
                      .enableAnalyzer(undefined)
                      .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                  }
                  Text('---------------------------').fontSize(14)
                  
                  Text('dynamicRangeMode').fontSize(22).margin({ bottom: 15 } as Margin)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .dynamicRangeMode(DynamicRangeMode.STANDARD)
                      .width(150)
                      .height(150)
                      .border({ width: 2, color: Color.Blue })
                    Image($r('app.media.startIcon'))
                      .dynamicRangeMode(undefined)
                      .width(150)
                      .height(150)
                      .border({ width: 2, color: Color.Blue })
                  }
                  Text('---------------------------').fontSize(14)
                }
              }
            })
          }
          ParallelizeUI({} as ParallelOption) {
            ForEach(forEachItems100,(item: Int, index: Double)=>{
              {
                Column(undefined) {
                  Text('image').fontSize(40)
                  Text('fillColor: Blue & syncLoad').fontSize(14)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .fillColor(Color.Blue)
                      .syncLoad(true)
                      .width(80)
                      .height(80)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.startIcon'))
                      .fillColor(undefined)
                      .syncLoad(undefined)
                      .width(80)
                      .height(80)
                      .border({ width: 1, color: Color.Black })
                  }
                  Text('---------------------------').fontSize(14)
                  Text('fitOriginalSize').fontSize(22).margin({ bottom: 15 } as Margin)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .fitOriginalSize(undefined)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.startIcon'))
                      .fitOriginalSize(true)
                      .border({ width: 1, color: Color.Black })
                  }
                  Text('---------------------------').fontSize(14)
                  Text('sourceSize').fontSize(22).margin({ bottom: 15 } as Margin)
                  
                  Row() {
                    Image($r('app.media.no8'))
                      .sourceSize({ width: 100, height: 100 })
                      .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.no8'))
                      .sourceSize(undefined)
                       .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                    }
                  Text('---------------------------').fontSize(14)
                  
                  Text('small & enableAnalyzer').fontSize(14)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .sourceSize({ width: 50, height: 50 })
                      .enableAnalyzer(true)
                      .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.startIcon'))
                      .sourceSize(undefined)
                      .enableAnalyzer(undefined)
                      .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                  }
                  Text('---------------------------').fontSize(14)
                  
                  Text('dynamicRangeMode').fontSize(22).margin({ bottom: 15 } as Margin)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .dynamicRangeMode(DynamicRangeMode.STANDARD)
                      .width(150)
                      .height(150)
                      .border({ width: 2, color: Color.Blue })
                    Image($r('app.media.startIcon'))
                      .dynamicRangeMode(undefined)
                      .width(150)
                      .height(150)
                      .border({ width: 2, color: Color.Blue })
                  }
                  Text('---------------------------').fontSize(14)
                }
              }
            })
          }
          ParallelizeUI({} as ParallelOption) {
            ForEach(forEachItems100,(item: Int, index: Double)=>{
              {
                Column(undefined) {
                  Text('image').fontSize(40)
                  Text('fillColor: Blue & syncLoad').fontSize(14)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .fillColor(Color.Blue)
                      .syncLoad(true)
                      .width(80)
                      .height(80)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.startIcon'))
                      .fillColor(undefined)
                      .syncLoad(undefined)
                      .width(80)
                      .height(80)
                      .border({ width: 1, color: Color.Black })
                  }
                  Text('---------------------------').fontSize(14)
                  Text('fitOriginalSize').fontSize(22).margin({ bottom: 15 } as Margin)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .fitOriginalSize(undefined)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.startIcon'))
                      .fitOriginalSize(true)
                      .border({ width: 1, color: Color.Black })
                  }
                  Text('---------------------------').fontSize(14)
                  Text('sourceSize').fontSize(22).margin({ bottom: 15 } as Margin)
                  
                  Row() {
                    Image($r('app.media.no8'))
                      .sourceSize({ width: 100, height: 100 })
                      .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.no8'))
                      .sourceSize(undefined)
                       .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                    }
                  Text('---------------------------').fontSize(14)
                  
                  Text('small & enableAnalyzer').fontSize(14)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .sourceSize({ width: 50, height: 50 })
                      .enableAnalyzer(true)
                      .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.startIcon'))
                      .sourceSize(undefined)
                      .enableAnalyzer(undefined)
                      .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                  }
                  Text('---------------------------').fontSize(14)
                  
                  Text('dynamicRangeMode').fontSize(22).margin({ bottom: 15 } as Margin)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .dynamicRangeMode(DynamicRangeMode.STANDARD)
                      .width(150)
                      .height(150)
                      .border({ width: 2, color: Color.Blue })
                    Image($r('app.media.startIcon'))
                      .dynamicRangeMode(undefined)
                      .width(150)
                      .height(150)
                      .border({ width: 2, color: Color.Blue })
                  }
                  Text('---------------------------').fontSize(14)
                }
              }
            })
          }
          ParallelizeUI({} as ParallelOption) {
            ForEach(forEachItems100,(item: Int, index: Double)=>{
              {
                Column(undefined) {
                  Text('image').fontSize(40)
                  Text('fillColor: Blue & syncLoad').fontSize(14)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .fillColor(Color.Blue)
                      .syncLoad(true)
                      .width(80)
                      .height(80)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.startIcon'))
                      .fillColor(undefined)
                      .syncLoad(undefined)
                      .width(80)
                      .height(80)
                      .border({ width: 1, color: Color.Black })
                  }
                  Text('---------------------------').fontSize(14)
                  Text('fitOriginalSize').fontSize(22).margin({ bottom: 15 } as Margin)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .fitOriginalSize(undefined)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.startIcon'))
                      .fitOriginalSize(true)
                      .border({ width: 1, color: Color.Black })
                  }
                  Text('---------------------------').fontSize(14)
                  Text('sourceSize').fontSize(22).margin({ bottom: 15 } as Margin)
                  
                  Row() {
                    Image($r('app.media.no8'))
                      .sourceSize({ width: 100, height: 100 })
                      .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.no8'))
                      .sourceSize(undefined)
                       .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                    }
                  Text('---------------------------').fontSize(14)
                  
                  Text('small & enableAnalyzer').fontSize(14)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .sourceSize({ width: 50, height: 50 })
                      .enableAnalyzer(true)
                      .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.startIcon'))
                      .sourceSize(undefined)
                      .enableAnalyzer(undefined)
                      .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                  }
                  Text('---------------------------').fontSize(14)
                  
                  Text('dynamicRangeMode').fontSize(22).margin({ bottom: 15 } as Margin)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .dynamicRangeMode(DynamicRangeMode.STANDARD)
                      .width(150)
                      .height(150)
                      .border({ width: 2, color: Color.Blue })
                    Image($r('app.media.startIcon'))
                      .dynamicRangeMode(undefined)
                      .width(150)
                      .height(150)
                      .border({ width: 2, color: Color.Blue })
                  }
                  Text('---------------------------').fontSize(14)
                }
              }
            })
          }
          ParallelizeUI({} as ParallelOption) {
            ForEach(forEachItems100,(item: Int, index: Double)=>{
              {
                Column(undefined) {
                  Text('image').fontSize(40)
                  Text('fillColor: Blue & syncLoad').fontSize(14)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .fillColor(Color.Blue)
                      .syncLoad(true)
                      .width(80)
                      .height(80)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.startIcon'))
                      .fillColor(undefined)
                      .syncLoad(undefined)
                      .width(80)
                      .height(80)
                      .border({ width: 1, color: Color.Black })
                  }
                  Text('---------------------------').fontSize(14)
                  Text('fitOriginalSize').fontSize(22).margin({ bottom: 15 } as Margin)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .fitOriginalSize(undefined)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.startIcon'))
                      .fitOriginalSize(true)
                      .border({ width: 1, color: Color.Black })
                  }
                  Text('---------------------------').fontSize(14)
                  Text('sourceSize').fontSize(22).margin({ bottom: 15 } as Margin)
                  
                  Row() {
                    Image($r('app.media.no8'))
                      .sourceSize({ width: 100, height: 100 })
                      .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.no8'))
                      .sourceSize(undefined)
                       .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                    }
                  Text('---------------------------').fontSize(14)
                  
                  Text('small & enableAnalyzer').fontSize(14)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .sourceSize({ width: 50, height: 50 })
                      .enableAnalyzer(true)
                      .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.startIcon'))
                      .sourceSize(undefined)
                      .enableAnalyzer(undefined)
                      .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                  }
                  Text('---------------------------').fontSize(14)
                  
                  Text('dynamicRangeMode').fontSize(22).margin({ bottom: 15 } as Margin)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .dynamicRangeMode(DynamicRangeMode.STANDARD)
                      .width(150)
                      .height(150)
                      .border({ width: 2, color: Color.Blue })
                    Image($r('app.media.startIcon'))
                      .dynamicRangeMode(undefined)
                      .width(150)
                      .height(150)
                      .border({ width: 2, color: Color.Blue })
                  }
                  Text('---------------------------').fontSize(14)
                }
              }
            })
          }
          ParallelizeUI({} as ParallelOption) {
            ForEach(forEachItems100,(item: Int, index: Double)=>{
              {
                Column(undefined) {
                  Text('image').fontSize(40)
                  Text('fillColor: Blue & syncLoad').fontSize(14)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .fillColor(Color.Blue)
                      .syncLoad(true)
                      .width(80)
                      .height(80)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.startIcon'))
                      .fillColor(undefined)
                      .syncLoad(undefined)
                      .width(80)
                      .height(80)
                      .border({ width: 1, color: Color.Black })
                  }
                  Text('---------------------------').fontSize(14)
                  Text('fitOriginalSize').fontSize(22).margin({ bottom: 15 } as Margin)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .fitOriginalSize(undefined)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.startIcon'))
                      .fitOriginalSize(true)
                      .border({ width: 1, color: Color.Black })
                  }
                  Text('---------------------------').fontSize(14)
                  Text('sourceSize').fontSize(22).margin({ bottom: 15 } as Margin)
                  
                  Row() {
                    Image($r('app.media.no8'))
                      .sourceSize({ width: 100, height: 100 })
                      .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.no8'))
                      .sourceSize(undefined)
                       .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                    }
                  Text('---------------------------').fontSize(14)
                  
                  Text('small & enableAnalyzer').fontSize(14)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .sourceSize({ width: 50, height: 50 })
                      .enableAnalyzer(true)
                      .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.startIcon'))
                      .sourceSize(undefined)
                      .enableAnalyzer(undefined)
                      .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                  }
                  Text('---------------------------').fontSize(14)
                  
                  Text('dynamicRangeMode').fontSize(22).margin({ bottom: 15 } as Margin)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .dynamicRangeMode(DynamicRangeMode.STANDARD)
                      .width(150)
                      .height(150)
                      .border({ width: 2, color: Color.Blue })
                    Image($r('app.media.startIcon'))
                      .dynamicRangeMode(undefined)
                      .width(150)
                      .height(150)
                      .border({ width: 2, color: Color.Blue })
                  }
                  Text('---------------------------').fontSize(14)
                }
              }
            })
          }
          ParallelizeUI({} as ParallelOption) {
            ForEach(forEachItems100,(item: Int, index: Double)=>{
              {
                Column(undefined) {
                  Text('image').fontSize(40)
                  Text('fillColor: Blue & syncLoad').fontSize(14)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .fillColor(Color.Blue)
                      .syncLoad(true)
                      .width(80)
                      .height(80)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.startIcon'))
                      .fillColor(undefined)
                      .syncLoad(undefined)
                      .width(80)
                      .height(80)
                      .border({ width: 1, color: Color.Black })
                  }
                  Text('---------------------------').fontSize(14)
                  Text('fitOriginalSize').fontSize(22).margin({ bottom: 15 } as Margin)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .fitOriginalSize(undefined)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.startIcon'))
                      .fitOriginalSize(true)
                      .border({ width: 1, color: Color.Black })
                  }
                  Text('---------------------------').fontSize(14)
                  Text('sourceSize').fontSize(22).margin({ bottom: 15 } as Margin)
                  
                  Row() {
                    Image($r('app.media.no8'))
                      .sourceSize({ width: 100, height: 100 })
                      .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.no8'))
                      .sourceSize(undefined)
                       .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                    }
                  Text('---------------------------').fontSize(14)
                  
                  Text('small & enableAnalyzer').fontSize(14)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .sourceSize({ width: 50, height: 50 })
                      .enableAnalyzer(true)
                      .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.startIcon'))
                      .sourceSize(undefined)
                      .enableAnalyzer(undefined)
                      .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                  }
                  Text('---------------------------').fontSize(14)
                  
                  Text('dynamicRangeMode').fontSize(22).margin({ bottom: 15 } as Margin)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .dynamicRangeMode(DynamicRangeMode.STANDARD)
                      .width(150)
                      .height(150)
                      .border({ width: 2, color: Color.Blue })
                    Image($r('app.media.startIcon'))
                      .dynamicRangeMode(undefined)
                      .width(150)
                      .height(150)
                      .border({ width: 2, color: Color.Blue })
                  }
                  Text('---------------------------').fontSize(14)
                }
              }
            })
          }
          ParallelizeUI({} as ParallelOption) {
            ForEach(forEachItems100,(item: Int, index: Double)=>{
              {
                Column(undefined) {
                  Text('image').fontSize(40)
                  Text('fillColor: Blue & syncLoad').fontSize(14)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .fillColor(Color.Blue)
                      .syncLoad(true)
                      .width(80)
                      .height(80)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.startIcon'))
                      .fillColor(undefined)
                      .syncLoad(undefined)
                      .width(80)
                      .height(80)
                      .border({ width: 1, color: Color.Black })
                  }
                  Text('---------------------------').fontSize(14)
                  Text('fitOriginalSize').fontSize(22).margin({ bottom: 15 } as Margin)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .fitOriginalSize(undefined)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.startIcon'))
                      .fitOriginalSize(true)
                      .border({ width: 1, color: Color.Black })
                  }
                  Text('---------------------------').fontSize(14)
                  Text('sourceSize').fontSize(22).margin({ bottom: 15 } as Margin)
                  
                  Row() {
                    Image($r('app.media.no8'))
                      .sourceSize({ width: 100, height: 100 })
                      .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.no8'))
                      .sourceSize(undefined)
                       .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                    }
                  Text('---------------------------').fontSize(14)
                  
                  Text('small & enableAnalyzer').fontSize(14)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .sourceSize({ width: 50, height: 50 })
                      .enableAnalyzer(true)
                      .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.startIcon'))
                      .sourceSize(undefined)
                      .enableAnalyzer(undefined)
                      .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                  }
                  Text('---------------------------').fontSize(14)
                  
                  Text('dynamicRangeMode').fontSize(22).margin({ bottom: 15 } as Margin)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .dynamicRangeMode(DynamicRangeMode.STANDARD)
                      .width(150)
                      .height(150)
                      .border({ width: 2, color: Color.Blue })
                    Image($r('app.media.startIcon'))
                      .dynamicRangeMode(undefined)
                      .width(150)
                      .height(150)
                      .border({ width: 2, color: Color.Blue })
                  }
                  Text('---------------------------').fontSize(14)
                }
              }
            })
          }
          ParallelizeUI({} as ParallelOption) {
            ForEach(forEachItems100,(item: Int, index: Double)=>{
              {
                Column(undefined) {
                  Text('image').fontSize(40)
                  Text('fillColor: Blue & syncLoad').fontSize(14)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .fillColor(Color.Blue)
                      .syncLoad(true)
                      .width(80)
                      .height(80)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.startIcon'))
                      .fillColor(undefined)
                      .syncLoad(undefined)
                      .width(80)
                      .height(80)
                      .border({ width: 1, color: Color.Black })
                  }
                  Text('---------------------------').fontSize(14)
                  Text('fitOriginalSize').fontSize(22).margin({ bottom: 15 } as Margin)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .fitOriginalSize(undefined)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.startIcon'))
                      .fitOriginalSize(true)
                      .border({ width: 1, color: Color.Black })
                  }
                  Text('---------------------------').fontSize(14)
                  Text('sourceSize').fontSize(22).margin({ bottom: 15 } as Margin)
                  
                  Row() {
                    Image($r('app.media.no8'))
                      .sourceSize({ width: 100, height: 100 })
                      .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.no8'))
                      .sourceSize(undefined)
                       .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                    }
                  Text('---------------------------').fontSize(14)
                  
                  Text('small & enableAnalyzer').fontSize(14)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .sourceSize({ width: 50, height: 50 })
                      .enableAnalyzer(true)
                      .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.startIcon'))
                      .sourceSize(undefined)
                      .enableAnalyzer(undefined)
                      .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                  }
                  Text('---------------------------').fontSize(14)
                  
                  Text('dynamicRangeMode').fontSize(22).margin({ bottom: 15 } as Margin)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .dynamicRangeMode(DynamicRangeMode.STANDARD)
                      .width(150)
                      .height(150)
                      .border({ width: 2, color: Color.Blue })
                    Image($r('app.media.startIcon'))
                      .dynamicRangeMode(undefined)
                      .width(150)
                      .height(150)
                      .border({ width: 2, color: Color.Blue })
                  }
                  Text('---------------------------').fontSize(14)
                }
              }
            })
          }
          ParallelizeUI({} as ParallelOption) {
            ForEach(forEachItems100,(item: Int, index: Double)=>{
              {
                Column(undefined) {
                  Text('image').fontSize(40)
                  Text('fillColor: Blue & syncLoad').fontSize(14)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .fillColor(Color.Blue)
                      .syncLoad(true)
                      .width(80)
                      .height(80)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.startIcon'))
                      .fillColor(undefined)
                      .syncLoad(undefined)
                      .width(80)
                      .height(80)
                      .border({ width: 1, color: Color.Black })
                  }
                  Text('---------------------------').fontSize(14)
                  Text('fitOriginalSize').fontSize(22).margin({ bottom: 15 } as Margin)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .fitOriginalSize(undefined)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.startIcon'))
                      .fitOriginalSize(true)
                      .border({ width: 1, color: Color.Black })
                  }
                  Text('---------------------------').fontSize(14)
                  Text('sourceSize').fontSize(22).margin({ bottom: 15 } as Margin)
                  
                  Row() {
                    Image($r('app.media.no8'))
                      .sourceSize({ width: 100, height: 100 })
                      .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.no8'))
                      .sourceSize(undefined)
                       .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                    }
                  Text('---------------------------').fontSize(14)
                  
                  Text('small & enableAnalyzer').fontSize(14)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .sourceSize({ width: 50, height: 50 })
                      .enableAnalyzer(true)
                      .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.startIcon'))
                      .sourceSize(undefined)
                      .enableAnalyzer(undefined)
                      .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                  }
                  Text('---------------------------').fontSize(14)
                  
                  Text('dynamicRangeMode').fontSize(22).margin({ bottom: 15 } as Margin)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .dynamicRangeMode(DynamicRangeMode.STANDARD)
                      .width(150)
                      .height(150)
                      .border({ width: 2, color: Color.Blue })
                    Image($r('app.media.startIcon'))
                      .dynamicRangeMode(undefined)
                      .width(150)
                      .height(150)
                      .border({ width: 2, color: Color.Blue })
                  }
                  Text('---------------------------').fontSize(14)
                }
              }
            })
          }
          ParallelizeUI({} as ParallelOption) {
            ForEach(forEachItems100,(item: Int, index: Double)=>{
              {
                Column(undefined) {
                  Text('image').fontSize(40)
                  Text('fillColor: Blue & syncLoad').fontSize(14)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .fillColor(Color.Blue)
                      .syncLoad(true)
                      .width(80)
                      .height(80)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.startIcon'))
                      .fillColor(undefined)
                      .syncLoad(undefined)
                      .width(80)
                      .height(80)
                      .border({ width: 1, color: Color.Black })
                  }
                  Text('---------------------------').fontSize(14)
                  Text('fitOriginalSize').fontSize(22).margin({ bottom: 15 } as Margin)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .fitOriginalSize(undefined)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.startIcon'))
                      .fitOriginalSize(true)
                      .border({ width: 1, color: Color.Black })
                  }
                  Text('---------------------------').fontSize(14)
                  Text('sourceSize').fontSize(22).margin({ bottom: 15 } as Margin)
                  
                  Row() {
                    Image($r('app.media.no8'))
                      .sourceSize({ width: 100, height: 100 })
                      .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.no8'))
                      .sourceSize(undefined)
                       .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                    }
                  Text('---------------------------').fontSize(14)
                  
                  Text('small & enableAnalyzer').fontSize(14)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .sourceSize({ width: 50, height: 50 })
                      .enableAnalyzer(true)
                      .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.startIcon'))
                      .sourceSize(undefined)
                      .enableAnalyzer(undefined)
                      .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                  }
                  Text('---------------------------').fontSize(14)
                  
                  Text('dynamicRangeMode').fontSize(22).margin({ bottom: 15 } as Margin)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .dynamicRangeMode(DynamicRangeMode.STANDARD)
                      .width(150)
                      .height(150)
                      .border({ width: 2, color: Color.Blue })
                    Image($r('app.media.startIcon'))
                      .dynamicRangeMode(undefined)
                      .width(150)
                      .height(150)
                      .border({ width: 2, color: Color.Blue })
                  }
                  Text('---------------------------').fontSize(14)
                }
              }
            })
          }
          ParallelizeUI({} as ParallelOption) {
            ForEach(forEachItems100,(item: Int, index: Double)=>{
              {
                Column(undefined) {
                  Text('image').fontSize(40)
                  Text('fillColor: Blue & syncLoad').fontSize(14)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .fillColor(Color.Blue)
                      .syncLoad(true)
                      .width(80)
                      .height(80)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.startIcon'))
                      .fillColor(undefined)
                      .syncLoad(undefined)
                      .width(80)
                      .height(80)
                      .border({ width: 1, color: Color.Black })
                  }
                  Text('---------------------------').fontSize(14)
                  Text('fitOriginalSize').fontSize(22).margin({ bottom: 15 } as Margin)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .fitOriginalSize(undefined)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.startIcon'))
                      .fitOriginalSize(true)
                      .border({ width: 1, color: Color.Black })
                  }
                  Text('---------------------------').fontSize(14)
                  Text('sourceSize').fontSize(22).margin({ bottom: 15 } as Margin)
                  
                  Row() {
                    Image($r('app.media.no8'))
                      .sourceSize({ width: 100, height: 100 })
                      .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.no8'))
                      .sourceSize(undefined)
                       .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                    }
                  Text('---------------------------').fontSize(14)
                  
                  Text('small & enableAnalyzer').fontSize(14)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .sourceSize({ width: 50, height: 50 })
                      .enableAnalyzer(true)
                      .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.startIcon'))
                      .sourceSize(undefined)
                      .enableAnalyzer(undefined)
                      .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                  }
                  Text('---------------------------').fontSize(14)
                  
                  Text('dynamicRangeMode').fontSize(22).margin({ bottom: 15 } as Margin)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .dynamicRangeMode(DynamicRangeMode.STANDARD)
                      .width(150)
                      .height(150)
                      .border({ width: 2, color: Color.Blue })
                    Image($r('app.media.startIcon'))
                      .dynamicRangeMode(undefined)
                      .width(150)
                      .height(150)
                      .border({ width: 2, color: Color.Blue })
                  }
                  Text('---------------------------').fontSize(14)
                }
              }
            })
          }
          ParallelizeUI({} as ParallelOption) {
            ForEach(forEachItems100,(item: Int, index: Double)=>{
              {
                Column(undefined) {
                  Text('image').fontSize(40)
                  Text('fillColor: Blue & syncLoad').fontSize(14)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .fillColor(Color.Blue)
                      .syncLoad(true)
                      .width(80)
                      .height(80)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.startIcon'))
                      .fillColor(undefined)
                      .syncLoad(undefined)
                      .width(80)
                      .height(80)
                      .border({ width: 1, color: Color.Black })
                  }
                  Text('---------------------------').fontSize(14)
                  Text('fitOriginalSize').fontSize(22).margin({ bottom: 15 } as Margin)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .fitOriginalSize(undefined)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.startIcon'))
                      .fitOriginalSize(true)
                      .border({ width: 1, color: Color.Black })
                  }
                  Text('---------------------------').fontSize(14)
                  Text('sourceSize').fontSize(22).margin({ bottom: 15 } as Margin)
                  
                  Row() {
                    Image($r('app.media.no8'))
                      .sourceSize({ width: 100, height: 100 })
                      .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.no8'))
                      .sourceSize(undefined)
                       .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                    }
                  Text('---------------------------').fontSize(14)
                  
                  Text('small & enableAnalyzer').fontSize(14)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .sourceSize({ width: 50, height: 50 })
                      .enableAnalyzer(true)
                      .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                    Image($r('app.media.startIcon'))
                      .sourceSize(undefined)
                      .enableAnalyzer(undefined)
                      .width(100)
                      .height(100)
                      .border({ width: 1, color: Color.Black })
                  }
                  Text('---------------------------').fontSize(14)
                  
                  Text('dynamicRangeMode').fontSize(22).margin({ bottom: 15 } as Margin)
                  Row() {
                    Image($r('app.media.startIcon'))
                      .dynamicRangeMode(DynamicRangeMode.STANDARD)
                      .width(150)
                      .height(150)
                      .border({ width: 2, color: Color.Blue })
                    Image($r('app.media.startIcon'))
                      .dynamicRangeMode(undefined)
                      .width(150)
                      .height(150)
                      .border({ width: 2, color: Color.Blue })
                  }
                  Text('---------------------------').fontSize(14)
                }
              }
            })
          }
        }
      }
    }
  }
}
