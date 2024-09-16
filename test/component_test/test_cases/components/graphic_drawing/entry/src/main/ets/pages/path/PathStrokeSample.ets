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
import pathStrokeTest from '../MyTest/PathStrokeTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct PathStrokeSample {
  @State pathStrokeColorValue1: Color | string = Color.Red
  @State pathStrokeColorValue2: number | Resource = 0x0000ff

  aboutToAppear(): void {
    loadComponentTestEntry(pathStrokeTest)
  }

  build() {
    Column({ space: 10 }) {
      Path()
        .width('210px')
        .height('310px')
        .commands('M100 0 L200 240 L0 240 Z')
        .stroke(this.pathStrokeColorValue1)
        .id('pathStroke1')
      Button('PathStroke1')
        .onClick(() => {
          this.pathStrokeColorValue1 = 'rgb(0,0,255)'
        })
      Path()
        .width('210px')
        .height('310px')
        .commands('M100 0 L200 240 L0 240 Z')
        .stroke(this.pathStrokeColorValue2)
        .id('pathStroke2')
      Button('PathStroke2')
        .onClick(() => {
          this.pathStrokeColorValue2 = $r('app.color.color_red')
        })
    }
  }
}