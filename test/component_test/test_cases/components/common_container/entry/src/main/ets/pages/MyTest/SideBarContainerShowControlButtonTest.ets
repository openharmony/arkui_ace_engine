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
import { logLibrary } from '@kit.PerformanceAnalysisKit'

export default async function sideBarContainerShowControlButtonTest() {
  /*
   * SideBarContainer组件 ShowControlButton属性
   * 找到id为sideBarContainerShowControlButton1的SideBarContainer组件
   * 找到画面文本为SideBarContainerShowControlButton的Button组件
   * 获取sideBarContainer1的AutoHide属性与期待值true比对
   * 点击button，变更sideBarContainer2的ShowControlButton属性值为false
   * 获取sideBarContainer1的ShowControlButton属性与期待值false比对
   */
  defineTest('sideBarContainerShowControlButtonTest', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('sideBarContainerShowControlButtonTestDemo running')
    let driver: Tester = Tester.create()
    let sideBarContainerShowControlButton1: Component = await driver.findComponent(Matcher.create()
      .id('sideBarContainerShowControlButton1')
      .enabled(true))
    let button: Component = await driver.findComponent((Matcher.create()
      .text('SideBarContainerShowControlButton')
      .enabled(true)))

    let showControlButton1: string = await sideBarContainerShowControlButton1.getInspectorInfo()
    assertTrue(JSON.parse(showControlButton1).$attrs.showControlButton)

    await button.tap()
    let showControlButton2: string = await sideBarContainerShowControlButton1.getInspectorInfo()
    assertFalse(JSON.parse(showControlButton2).$attrs.showControlButton)
  }, 0)
}