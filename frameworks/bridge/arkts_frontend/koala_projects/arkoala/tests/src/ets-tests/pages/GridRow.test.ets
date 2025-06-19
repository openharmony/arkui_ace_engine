/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

@Entry
@Component
struct GridRowTest {

  build() {
    Grid() {
      GridRow(
      {
        columns: { xs: 21, sm: 22, md: 23, lg: 24, xl: 25, xxl: 26 },
        gutter: { x: { xs: 77, sm: 55, md: 44, lg: 33, xl: 22, xxl: 11 },
          y: { xs: 97, sm: 98, md: 99, lg: 90, xl: 91, xxl: 92 } 
        },
        breakpoints: { value: ["400vp", "600fp", "700px"],
          reference: BreakpointsReference.ComponentSize
        },
        direction: GridRowDirection.Row
      }) {
        Text("Grid row")
      }
      .alignItems(ItemAlign.Center)

      GridRow(
      {
        columns: 5,
        gutter: {x: 7, y: 9},
        breakpoints: { value: ["200lpx", "500px", "900fp"],
          reference: BreakpointsReference.WindowSize
        },
        direction: GridRowDirection.RowReverse
      }) {
        Text("Grid row")
      }
      .alignItems(ItemAlign.Start)
    }
  }
}
