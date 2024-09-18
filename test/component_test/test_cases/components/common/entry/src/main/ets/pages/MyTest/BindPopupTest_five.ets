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


import { assertEqual, assertFalse, assertTrue, MatchType } from '@ohos.arkui.componentTest'
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'

export default async function bindPopupTest_five() {
  /*
   * BindPopup 通用属性
   * 找到画面文本为 CustomPopup 的组件 获取它的type存放在 popupBuilder中
   * popupBuilder 与 'Text' 比对
   * 找到画面id为 buttonBindPopup5 的 Button 组件
   * 找到画面文本为 ButtonBindPopup1 ButtonBindPopup2 的 Button 组件
   * 获取 buttonBindPopup5 的 BindPopup.show 属性与期望值 true 比对
   * popup.placement 属性与期望值 Placement.Left 比对
   * popup.popupColor 属性与期望值 Color.Green 比对
   * popup.enableArrow 属性与期望值 true 比对
   * popup.autoCancel 属性与期望值 true 比对
   * 点击 button1 变更 buttonBindPopup5 的BindPopup.show属性为false
   * 获取 BindPopup.show 的属性与期望值 false 比对
   * 点击 button2 变更 buttonBindPopup5 的popup.enableArrow 和 popup.autoCancel 属性 为 false
   * 获取 popup.enableArrow 和 popup.autoCancel 的属性与期望值 false 比对
   * */
  defineTest('bindPopupTest_fiveDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('bindPopupTest_fiveDemo running')
    let driver: Tester = Tester.create()
    let customPopup: Component = await driver.findComponent(Matcher.create().text('CustomPopup').enabled(true))
    let popupBuilder: string = await customPopup.getType()
    assertEqual(popupBuilder, 'Text')
    let buttonBindPopup5: Component = await driver.findComponent(Matcher.create().id('buttonBindPopup5').enabled(true))
    let button1: Component =
      await driver.findComponent(Matcher.create().text('ButtonBindPopup1', MatchType.EQUALS).enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('ButtonBindPopup2').enabled(true))
    let bindPopup1: string = await buttonBindPopup5.getInspectorInfo()
    assertFalse(JSON.parse(bindPopup1).$attrs.BindPopup == undefined)
    assertTrue(JSON.parse(bindPopup1).$attrs.BindPopup.show)
    assertEqual(JSON.parse(bindPopup1)
      .$attrs
      .BindPopup
      .popup
      .placement, Placement.Left)
    assertEqual(JSON.parse(bindPopup1)
      .$attrs
      .BindPopup
      .popup
      .popupColor, Color.Green)
    assertTrue(JSON.parse(bindPopup1)
      .$attrs
      .BindPopup
      .popup
      .enableArrow)
    assertTrue(JSON.parse(bindPopup1)
      .$attrs
      .BindPopup
      .popup
      .autoCancel)

    await button1.tap()
    let bindPopup2: string = await buttonBindPopup5.getInspectorInfo()
    assertFalse(JSON.parse(bindPopup2).$attrs.BindPopup.show)

    await button2.tap()
    let bindPopup3: string = await buttonBindPopup5.getInspectorInfo()
    assertFalse(JSON.parse(bindPopup3)
      .$attrs
      .BindPopup
      .popup
      .enableArrow)
    assertFalse(JSON.parse(bindPopup3)
      .$attrs
      .BindPopup
      .popup
      .autoCancel)
  }, 0)
}