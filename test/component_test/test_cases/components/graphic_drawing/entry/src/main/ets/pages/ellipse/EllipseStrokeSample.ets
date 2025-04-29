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
import ellipseStrokeTest from '../MyTest/EllipseStrokeTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct EllipseStrokeSample {
  @State ellipseStrokeColorValue1: Color | number = Color.Red
  @State ellipseStrokeColorValue2: Resource | string = $r('app.color.color_red')

  aboutToAppear(): void {
    loadComponentTestEntry(ellipseStrokeTest)
  }

  build() {
    Column({ space: 10 }) {
      Ellipse({ width: 150, height: 90 })
        .stroke(this.ellipseStrokeColorValue1)
        .id('ellipseStroke1')
      Button('EllipseStroke1')
        .onClick(() => {
          this.ellipseStrokeColorValue1 = 0x0000ff
        })
      Ellipse({ width: 150, height: 90 })
        .stroke(this.ellipseStrokeColorValue2)
        .id('ellipseStroke2')
      Button('EllipseStroke2')
        .onClick(() => {
          this.ellipseStrokeColorValue2 = 'rgb(0,0,255)'
        })
    }
  }
}