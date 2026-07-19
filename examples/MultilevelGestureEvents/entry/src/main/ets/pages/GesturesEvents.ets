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
@Entry
@Component
struct Index {
  build() {
    Column() {
      // [Start priorityfirst_gesture]
      Column() {
        Column().id('ComponentB').gesture(TapGesture({ count: 1 }))
      }.id('ComponentA').gesture(TapGesture({ count: 1 }))
      // [End priorityfirst_gesture]

      // [Start prioritysecond_gesture]
      Column()
        .id('ComponentA')
        .gesture(
          GestureGroup(
            GestureMode.Exclusive,
            TapGesture({count: 1}),
            PanGesture({distance: 5})
          )
        )
      // [End prioritysecond_gesture]
    }
    .width('100%')
    .height('100%')
    .padding(20)
    .backgroundColor(Color.White)
    .justifyContent(FlexAlign.Start)
  }
}