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
struct GridItemTest {
  @State data: String[] = ['0', '1']

  build() {
    Grid() {
      ForEach(this.data, (day1: string) => {
        ForEach(this.data, (day2: string) => {
          GridItem() {
            Text("Grid item: " + day1 + day2)
          }
          .rowStart(5)
          .rowEnd(9)
          .columnStart(2)
          .columnEnd(7)
          .selectable(true)
          .selected(false)
          .forceRebuild(true)
        }, day2 => day2)
      }, day1 => day1)
    }
  }
}
