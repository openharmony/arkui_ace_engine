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
  assertEqual,
  assertFalse,
  Component,
  defineTest,
  Matcher,
  TestCaseLevel,
  Tester
} from '@ohos.arkui.componentTest'

export default async function navDestinationModeTest() {
  /*
* NavDestination组件 Mode属性
* 找到画面文本为PushNavDestination的button组件
* 点击button1，跳转到NavDestination组件所在界面
* 找到画面id为navDestinationMode的NavDestination组件
* 找到画面文本为NavDestinationMode的button组件
* 获取navDestination的Mode属性与期待值NavDestinationMode.STANDARD比对
* 点击button2，变更navDestination的Mode属性值为NavDestinationMode.DIALOG
* 获取navDestination的Mode属性与期待值NavDestinationMode.DIALOG比对
*/
  defineTest('navDestinationModeTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("navDestinationModeTestDemo running")
    let driver: Tester = Tester.create()
    let button1: Component = await driver.findComponent(Matcher.create().text('PushNavDestination').enabled(true))
    await button1.tap()

    let navDestination: Component = await driver.findComponent(Matcher.create().id('navDestinationMode').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('NavDestinationMode').enabled(true))

    let mode1: string = await navDestination.getInspectorInfo()
    assertFalse(JSON.parse(mode1).$attrs.mode == undefined)
    assertEqual(JSON.parse(mode1).$attrs.mode, NavDestinationMode.STANDARD)

    await button2.tap()
    let mode2: string = await navDestination.getInspectorInfo()
    assertEqual(JSON.parse(mode2).$attrs.mode, NavDestinationMode.DIALOG)
  }, 0)
}