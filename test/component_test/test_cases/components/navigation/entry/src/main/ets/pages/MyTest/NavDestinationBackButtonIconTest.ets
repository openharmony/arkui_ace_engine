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

export default async function navDestinationBackButtonIconTest() {
  /*
* NavDestination组件 BackButtonIcon属性
* 找到画面文本为PushNavDestination的button组件
* 点击button1，跳转到NavDestination组件所在界面
* 找到画面id为navDestinationBackButtonIcon的NavDestination组件
* 找到画面文本为NavDestinationBackButtonIcon1,NavDestinationBackButtonIcon2的button组件
* 获取navDestination的BackButtonIcon属性与期待值'../../../resources/base/media/icon.png'比对
* 点击button2，变更navDestination的BackButtonIcon属性值为$r('app.media.startIcon')
* 获取navDestination的BackButtonIcon属性与期待值$r('app.media.startIcon')比对
* 点击button3，变更navDestination的BackButtonIcon属性值为srcPixelMap
* 获取navDestination的BackButtonIcon属性与期待值'srcPixelMap'比对
*/
  defineTest('navDestinationBackButtonIconTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("navDestinationBackButtonIconTestDemo running")
    let driver: Tester = Tester.create()
    let button1: Component = await driver.findComponent(Matcher.create().text('PushNavDestination').enabled(true))
    await button1.tap()

    let navDestination: Component =
      await driver.findComponent(Matcher.create().id('navDestinationBackButtonIcon').enabled(true))
    let button2: Component =
      await driver.findComponent(Matcher.create().text('NavDestinationBackButtonIcon1').enabled(true))
    let button3: Component =
      await driver.findComponent(Matcher.create().text('NavDestinationBackButtonIcon2').enabled(true))

    let backButtonIcon1: string = await navDestination.getInspectorInfo()
    assertFalse(JSON.parse(backButtonIcon1).$attrs.backButtonIcon == undefined)
    assertEqual(JSON.parse(backButtonIcon1).$attrs.backButtonIcon, '../../../resources/base/media/icon.png')
    await button2.tap()
    let backButtonIcon2: string = await navDestination.getInspectorInfo()
    assertEqual(JSON.parse(backButtonIcon2).$attrs.backButtonIcon, $r('app.media.startIcon'))

    await button3.tap()
    let backButtonIcon3: string = await navDestination.getInspectorInfo()
    assertEqual(JSON.parse(backButtonIcon3).$attrs.backButtonIcon, 'srcPixelMap')
  }, 0)
}