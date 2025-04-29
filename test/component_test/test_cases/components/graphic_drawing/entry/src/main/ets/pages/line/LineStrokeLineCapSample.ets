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
import lineStrokeLineCapTest from '../MyTest/LineStrokeLineCapTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct LineStrokeLineCapSample {
  @State lineStrokeLineCapType: LineCapStyle = LineCapStyle.Round

  aboutToAppear(): void {
    loadComponentTestEntry(lineStrokeLineCapTest)
  }

  build() {
    Column({ space: 10 }) {
      Line()
        .width(100)
        .height(200)
        .startPoint([50, 50])
        .endPoint([50, 200])
        .stroke(Color.Blue)
        .strokeWidth(20)
        .strokeLineCap(LineCapStyle.Butt)
        .id('lineStrokeLineCap1')
      Line()
        .width(100)
        .height(200)
        .startPoint([50, 50])
        .endPoint([50, 200])
        .stroke(Color.Blue)
        .strokeWidth(20)
        .strokeLineCap(this.lineStrokeLineCapType)
        .id('lineStrokeLineCap2')
      Button('LineStrokeLineCap')
        .onClick(() => {
          this.lineStrokeLineCapType = LineCapStyle.Square
        })
    }
  }
}