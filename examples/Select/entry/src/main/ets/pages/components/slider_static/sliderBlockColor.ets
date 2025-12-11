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
'use static'
import { Entry, Text, Row, RowOptions, Column, Component, Button, ClickEvent, LinearGradient, ColumnOptions,
  ResourceColor, Slider, SliderStyle, Axis, $r, Color } from '@ohos.arkui.component'
import { State } from '@ohos.arkui.stateManagement'
import hilog from '@ohos.hilog'

@Builder
export function SliderBlockColorStaticBuilder(name: string, param: Object) {
  SliderBlockColorStatic()
}
@Entry
@Component
struct SliderBlockColorStatic {
  @State colorGradient: LinearGradient = 
    new LinearGradient([{ color: '#FFFFFF', offset: 0 }, { color: '#007DFF', offset: 1 }])
  private resColor0: ResourceColor = Color.Pink;
  private resColor1: ResourceColor = $r('app.color.green_color');
  private resColor2: ResourceColor = '#0000ff';
  private resColor3: ResourceColor = 'rgb(255, 0, 0)';

  build() {
    Column({ space: 10 } as ColumnOptions) {
      Row(){
        Slider({
          style:SliderStyle.OutSet,
          value:50,
          min: 0,
          max: 100,
        })
          .blockColor(this.colorGradient)
          .blockSize({width:'50vp',height:'50vp'})
      }.width('80%')
      Row(){
        Slider({
          style:SliderStyle.InSet,
          value:50,
          min: 0,
          max: 100,
        })
          .blockColor(this.colorGradient)
          .blockSize({width:'50vp',height:'50vp'})
      }.width('80%')
      Row(){
        Slider({
          style:SliderStyle.NONE,
          value:50,
          min: 0,
          max: 100,
        })
          .blockColor(this.colorGradient)
          .blockSize({width:'50vp',height:'50vp'})
      }.width('80%')
    }.width('100%')

  }
}
