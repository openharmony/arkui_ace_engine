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

/**
 * Image HDR Test Component
 *
 * This component demonstrates how to test and display High Dynamic Range (HDR) images using the `dynamicRangeMode`
 * property. It supports switching between different dynamic range modes, including HIGH, CONSTRAINT, and STANDARD,
 * to visualize how image rendering adapts to various display capabilities. Users can toggle image visibility and
 * dynamically switch between HDR modes via interactive buttons.
 */
@Entry
@Component
struct ImageHDRTest {
  @State show: Boolean = true
  @State het: number = 216
  @State wid: number = 384
  @State parmDynamicRangeModeStr: string[] = [
    'dynamicRangeMode = HIGH','dynamicRangeMode = CONSTRAINT','dynamicRangeMode = STANDARD'
  ]
  @State parmDynamicRangeMode: DynamicRangeMode[] = [
    DynamicRangeMode.HIGH, DynamicRangeMode.CONSTRAINT, DynamicRangeMode.STANDARD
  ]
  @State parm: DynamicRangeMode | undefined |number = DynamicRangeMode.HIGH
  @State idx1: number = 0
  build() {
    Column(){
      Blank()
        .height(100)
      Text('Image的HDR测试Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
      Divider()
      Button('IsShow')
        .onClick(() => {
          if (this.show) {
            this.show = false;
          } else {
            this.show = true;
          }
        })
      Divider()
      Button('Change idx_DynamicRangeMode++ = ' + this.idx1)
        .onClick(()=>{
          this.idx1 = (this.idx1 + 1) % 3
        })
      if (this.show) {
        Divider()
        Text(this.parmDynamicRangeModeStr[this.idx1])
          .fontWeight(FontWeight.Bolder)
        Divider()
        Image($r('app.media.JPEGVividSingle'))
          .height(this.het)
          .width(this.wid)
          .dynamicRangeMode(this.parmDynamicRangeMode[this.idx1])
      }
    }.backgroundColor('#CCCCCC').width('100%').height('100%')
  }
}