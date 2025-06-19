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
struct GridColTest {

  build() {
    Grid() {
      GridCol() {
        Text("Grid col")
      }
      .span({ xs: 1, sm: 2, md: 3, lg: 4, xl: 5, xxl: 6 })
      .gridColOffset({ xs: 11, sm: 22, md: 33, lg: 44, xl: 55, xxl: 77 })
      .order({ xs: 91, sm: 92, md: 93, lg: 94, xl: 95, xxl: 96 })

      GridCol({ span: 5, offset: 7, order: 9 }) {}
    }
  }
}
