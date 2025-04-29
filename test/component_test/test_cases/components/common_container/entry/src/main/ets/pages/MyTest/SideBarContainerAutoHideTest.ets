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

export default async function sideBarContainerAutoHideTest() {
  /*
   * SideBarContainer组件 AutoHide属性
   * 找到id为sideBarContainerAutoHide1，sideBarContainerAutoHide2的SideBarContainer组件
   * 找到画面文本为SideBarContainerAutoHide的Button组件
   * 获取sideBarContainer1的AutoHide属性与期待值true比对
   * 获取sideBarContainer2的AutoHide属性与期待值false比对
   * 点击button，变更sideBarContainer2的AutoHide属性值为true
   * 获取sideBarContainer2的AutoHide属性与期待值true比对
   */
  defineTest('sideBarContainerAutoHideTest', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('sideBarContainerAutoHideTestDemo running')
    let driver: Tester = Tester.create()
    let sideBarContainerAutoHide1: Component = await driver.findComponent(Matcher.create()
      .id('sideBarContainerAutoHide1')
      .enabled(true))
    let sideBarContainerAutoHide2: Component = await driver.findComponent(Matcher.create()
      .id('sideBarContainerAutoHide2')
      .enabled(true))
    let button: Component = await driver.findComponent((Matcher.create()
      .text('SideBarContainerAutoHide')
      .enabled(true)))

    let autoHide1: string = await sideBarContainerAutoHide1.getInspectorInfo()
    assertTrue(JSON.parse(autoHide1).$attrs.autoHide)

    let autoHide2: string = await sideBarContainerAutoHide2.getInspectorInfo()
    assertFalse(JSON.parse(autoHide2).$attrs.autoHide)
    await button.tap()
    let autoHide3: string = await sideBarContainerAutoHide2.getInspectorInfo()
    assertTrue(JSON.parse(autoHide3).$attrs.autoHide)
  }, 0)
}