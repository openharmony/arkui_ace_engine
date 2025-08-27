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
import { Box, OutlinedButton } from "@koalaui/arkoala-extension-component"

@Entry
@Component
export struct Index {
    build() {
      Column() {
        Box({ width: 300, height: 295, color: 0xe6e6e6 }, () => {
          Button("TopStart").align(Alignment.TopStart)
          Button("Center").align(Alignment.Center)
          OutlinedButton({
            label: "Outlined",
            width: 150,
            height: 50,
            backgroundColor: Color.Red,
            align: Alignment.TopEnd,
            onOutlineChange: (thickness: number, color: Color) => {
              console.log("OutlinedButtonPeer.outline:", thickness, color)
            },
            outline: { thickness: 2, color: Color.Red }
          })
          Row({ space: 10 }) {
            Button("1")
            Button("2")
            Button("3")
          }
          .backgroundColor(Color.Gray)
          .align(Alignment.BottomEnd)
          .width(150)
        })
      }.width(600).height(600).backgroundColor(0xaaaaaa)
    }
}

