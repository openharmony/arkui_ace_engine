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
struct SideBarContainerTest {
    build() {
        SideBarContainer(SideBarContainerType.AUTO) {
            Text("SideBarContainer Test")
        }
        .showSideBar(true)
        .showControlButton(false)
        .sideBarWidth("123vp")
        .minSideBarWidth("111px")
        .maxSideBarWidth("222fp")
        .autoHide(true)
        .sideBarPosition(SideBarPosition.End)
        .minContentWidth("333px")
        .divider({ strokeWidth: 55, color: 0xff00ff, startMargin: "7px", endMargin: "8vp" })
        .controlButton({left: 10, top: 20, width: 30, height: 40, icons: {shown: "/shownIcon", hidden: "/hiddenIcon", switching: "/switchingIcon"}})
    }
}