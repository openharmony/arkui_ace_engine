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

export default async function navDestinationHideTitleBarTest() {
  /*
* NavDestination组件 HideTitleBar属性
* 找到画面文本为PushNavDestination的button组件
* 点击button1，跳转到NavDestination组件所在界面
* 找到画面id为navDestinationHideTitleBar的NavDestination组件
* 找到画面文本为NavDestinationHideTitleBar的button组件
* 获取navDestination的HideTitleBar属性与期待值false比对
* 点击button2，变更navDestination的HideTitleBar属性值为true
* 获取navDestination的HideTitleBar属性与期待值true比对
*/
  defineTest('navDestinationHideTitleBarTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("navDestinationHideTitleBarTestDemo running")
    let driver: Tester = Tester.create()
    let button1: Component = await driver.findComponent(Matcher.create().text('PushNavDestination').enabled(true))
    await button1.tap()

    let navDestination: Component =
      await driver.findComponent(Matcher.create().id('navDestinationHideTitleBar').enabled(true))
    let button2: Component =
      await driver.findComponent(Matcher.create().text('NavDestinationHideTitleBar').enabled(true))

    let hideTitleBar1: string = await navDestination.getInspectorInfo()
    assertFalse(JSON.parse(hideTitleBar1).$attrs.hideTitleBar == undefined)
    assertFalse(JSON.parse(hideTitleBar1).$attrs.hideTitleBar)

    await button2.tap()
    let hideTitleBar2: string = await navDestination.getInspectorInfo()
    assertTrue(JSON.parse(hideTitleBar2).$attrs.hideTitleBar)
  }, 0)
}