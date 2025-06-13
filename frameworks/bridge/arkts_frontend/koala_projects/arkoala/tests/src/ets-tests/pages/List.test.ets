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
struct ListTest {
    build() {
        Column() {
            Text("ListTest")
            List({initialIndex: 3, space: 22})
            .lanes(10, "15px")
            .listDirection(Axis.Horizontal)
            .editMode(true)
            .multiSelectable(true)
            .chainAnimation(true)
            .cachedCount(1)
            .sticky(StickyStyle.Footer)
            .edgeEffect(EdgeEffect.None, {alwaysEnabled: true})
            .scrollBar(BarState.On)
            .alignListItem(ListItemAlign.Center)
            .scrollSnapAlign(ScrollSnapAlign.CENTER)
            .enableScrollInteraction(true)
            .friction(10.5)
            .nestedScroll({ scrollForward: NestedScrollMode.SELF_FIRST,
                           scrollBackward: NestedScrollMode.PARALLEL
            })
            .divider({ strokeWidth: 55, color: 0xff00ff, startMargin: "7px", endMargin: "8vp" })
            .chainAnimationOptions(
               { minSpace: 11, maxSpace: "22px", conductivity: 3, intensity: 4, edgeEffect: ChainEdgeEffect.STRETCH, stiffness: 5, damping: 7 })
            .contentStartOffset(33.3)
            .contentEndOffset(99.9)
            .scrollBarColor("0xfedcba")
            .scrollBarWidth("20px")
        }
    }
}