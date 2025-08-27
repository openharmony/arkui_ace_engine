/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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

@Styles function myStyles() {
  .opacity(1)
  .backgroundColor(Color.Red)
  .animation({ delay: 100, duration: 1000 })
  .width(100)
  .animation({ duration: 2000 })
  .height(100)
  .borderRadius(10)
  .animation({
    delay: 100,
    curve: Curve.EaseOut,
    duration: 3000
  })
}

@Entry
@Component
struct AnimationExample {
  @State myOpacity: number = 1
  @State myColor: Color = Color.Red
  @State myWidth: number = 100
  @State myHeight: number = 100
  @State myRadius: number = 10
  build() {
    Column()
      .myStyles()
      .opacity(this.myOpacity)
      .backgroundColor(this.myColor)
      .animation({ delay: 100, duration: 1000 })
      .width(this.myWidth)
      .animation({ duration: 2000 })
      .height(this.myHeight)
      .borderRadius(this.myRadius)
      .animation({
        delay: 100,
        curve: Curve.EaseOut,
        duration: 3000
      })
      .onClick(() => {
        this.myOpacity = 0.5
        this.myColor = Color.Green
        this.myWidth = 200
        this.myHeight = 200
        this.myRadius = 20
      })
  }
}
