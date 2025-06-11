/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

// @Entry  Commented for now as it causes the plugin to emit router code
@Component
export struct MyComponent {
    @State count: number = 17
    @State other: number = 42

    build() {
        Column() {
         Text('media/1.jpg')
          .width("80%")
          .height("20%")
          .backgroundColor(this.count > 20 ? Color.Yellow : Color.Red )
          .margin({top:30})
          .padding(20)

        Row()
        .width('90%')
        .height(50)
        .linearGradient({
          angle: 90,
          colors: [[0xff0000, 0.0], [0x0000ff, 0.3], [0xffff00, 1.0]]
        })

        Text("Black Color").backgroundColor(0xFF000000).margin(20)
        Text('This is Arkoala UI').opacity(0.4)
        Text('Visibility').visibility(Visibility.Hidden)


        Text('This is Arkoala UI').opacity(0.4)
        Text('Color 0xbbb2cb')
          .backgroundColor(0xbbb2cb)
        }
        .height(this.count + 150)
        .width(150 + this.other)
        .height(777)

        Child()
    }
}

@Component
struct Child {
    @State count: number = 10

    build() {
        Button("Button")
            .width(this.count + 200)
            .onClick(e => {
                console.log("ARK2", e)
                this.count++
            })

    }
}
