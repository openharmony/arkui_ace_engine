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
struct GridTest {

  build() {
    Grid() {
      Text("Grid")
    }
    .columnsTemplate("1fr 2fr 3fr")
    .rowsTemplate("3fr 2fr 1fr")
    .columnsGap(5)
    .rowsGap("10px")
    .scrollBarWidth("5fp")
    .scrollBarColor("#abcdef")
    .scrollBar(BarState.On)
    .cachedCount(10)
    .editMode(true)
    .multiSelectable(false)
    .maxCount(100)
    .minCount(5)
    .cellLength(77)
    .layoutDirection(GridDirection.ColumnReverse)
    .supportAnimation(true)
    .edgeEffect(EdgeEffect.Spring)
    .nestedScroll({scrollForward: NestedScrollMode.SELF_ONLY, scrollBackward: NestedScrollMode.SELF_FIRST})
    .enableScrollInteraction(true)
    .friction(100)
  }
}
