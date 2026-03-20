/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

// xxx.ets
import { CircleShape, EllipseShape, PathShape, promptAction, RectShape } from '@kit.ArkUI'

@Entry
@Component
struct TapGestureExample {
  @State value: string = ''
  @State text: string = ''
  @State dis: number = 0
  @State clipShapeTest: CircleShape | EllipseShape | PathShape | RectShape = new CircleShape({ width: 55.555, height: 44.444 })
  @State show: boolean = false
  build() {
    Column({space: 5}) {
      if (this.show) {
        Text("opacity(0.2)")
          .fontSize(20)
          .width("String")
          .height(150)
          .textAlign(TextAlign.Center)
          .backgroundColor("#ffe20d3f")
          .id("idY")
          .borderWidth(30)// .opacity(0.2)
          .mask(new ProgressMask(150, 5, Color.Gray))
        // .mask(new ProgressMask(1, 300, Color.Black))
      }
      Text("noOpacity")
        .fontSize(20)
        .width(300)
        .height(150)
        .textAlign(TextAlign.Center)
        .backgroundColor("#ffe20d3f")
        .id("idY")
        .borderWidth(30)
      Button("click")
        .onClick(()=>{
          this.show = !this.show
        })
    }
    .height("100%")
    .width("100%")
    .border({ width: 3 })
  }
}
