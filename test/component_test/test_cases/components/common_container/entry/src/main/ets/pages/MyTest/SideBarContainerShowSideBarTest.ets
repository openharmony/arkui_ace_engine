/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

import {
  assertFalse,
  assertTrue,
  Component,
  defineTest,
  Matcher,
  TestCaseLevel,
  Tester
} from '@ohos.arkui.componentTest'

export default async function sideBarContainerShowSideBarTest() {
  /*
   * SideBarContainer组件 ShowSideBar属性
   * 找到id为sideBarContainerShowSideBar1的SideBarContainer组件
   * 找到画面文本为SideBarContainerShowControlButton的Button组件
   * 获取sideBarContainer1的ShowSideBar属性与期待值false比对
   * 点击button，变更sideBarContainer1的ShowControlButton属性值为true
   * 获取sideBarContainer1的ShowControlButton属性与期待值true比对
   */
  defineTest('sideBarContainerShowSideBarTest', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('sideBarContainerShowSideBarTestDemo running')
    let driver: Tester = Tester.create()
    let sideBarContainerShowSideBar1: Component = await driver.findComponent(Matcher.create()
      .id('sideBarContainerShowSideBar1')
      .enabled(true))
    let button: Component = await driver.findComponent((Matcher.create()
      .text('SideBarContainerShowSideBar')
      .enabled(true)))

    let showSideBar1: string = await sideBarContainerShowSideBar1.getInspectorInfo()
    assertFalse(JSON.parse(showSideBar1).$attrs.showSideBar)
    await button.tap()
    let showSideBar2: string = await sideBarContainerShowSideBar1.getInspectorInfo()
    assertTrue(JSON.parse(showSideBar2).$attrs.showSideBar)
  }, 0)
}