/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
// 测试代码路径
import ellipseFillColorTest from '../MyTest/EllipseFillTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct EllipseFillSample {
  @State ellipseFillColorValue1: Color | number = Color.Red
  @State ellipseFillColorValue2: Resource | string = $r('app.color.color_red')

  aboutToAppear(): void {
    loadComponentTestEntry(ellipseFillColorTest)
  }

  build() {
    Column({ space: 10 }) {
      Ellipse({ width: 150, height: 80 })
        .fill(this.ellipseFillColorValue1)
        .id('ellipseFill1')
      Button('EllipseFill1')
        .onClick(() => {
          this.ellipseFillColorValue1 = 0x0000ff
        })
      Ellipse({ width: 150, height: 80 })
        .fill(this.ellipseFillColorValue2)
        .id('ellipseFill2')
      Button('EllipseFill2')
        .onClick(() => {
          this.ellipseFillColorValue2 = 'rgb(0,0,255)'
        })
    }
  }
}