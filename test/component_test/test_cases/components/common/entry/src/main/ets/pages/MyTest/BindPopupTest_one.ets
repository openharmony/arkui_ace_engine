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

import { assertEqual, assertFalse, assertTrue } from '@ohos.arkui.componentTest'
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'

export default async function bindPopupTest_one() {
  /*
   * BindPopup 通用属性
   * 找到画面id为 buttonBindPopup1 的 Button 组件
   * 找到画面文本为 Button_bindPopup 的 Button 组件
   * 获取 buttonBindPopup1 的 BindPopup.show 属性与期望值 true 比对
   * popup.message 的属性与期望值 "bindPopup" 比对
   * popup.placementOnTop 的属性与期望值 true 比对
   * popup.primaryButton.value 的属性与期望值 'confirm' 比对
   * popup.secondaryButton.value 的属性与期望值 'cancel' 比对5
   * 获取 text 为 'confirm' 的 Button 按钮
   * 点击 button1 变更 buttonBindPopup1 属性
   * 获取 buttonBindPopup1 的 bindPopup.show 属性与 false 对比
   * 获取 buttonBindPopup1 的bindPopup.show属性与 false 对比
   * 获取 buttonBindPopup1 的bindPopup.show属性与 false 对比
   * BindPopup.show 的属性与期望值 false 比对
   * */
  defineTest('bindPopupTest_oneDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('bindPopupTest_oneDemo running')
    let driver: Tester = Tester.create()
    let buttonBindPopup1: Component = await driver.findComponent(Matcher.create().id('buttonBindPopup1').enabled(true))
    let buttonEnabled: Component = await driver.findComponent(Matcher.create().id('ButtonEnabled').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ButtonBindPopup').enabled(true))
    let bindPopup1: string = await buttonBindPopup1.getInspectorInfo()
    assertFalse(JSON.parse(bindPopup1).$attrs.bindPopup == undefined)

    assertTrue(JSON.parse(bindPopup1).$attrs.bindPopup)
    assertEqual(JSON.parse(bindPopup1)
      .$attrs
      .bindPopup
      .popup
      .message, "bindPopup")
    assertTrue(JSON.parse(bindPopup1)
      .$attrs
      .bindPopup
      .popup
      .placementOnTop)
    assertEqual(JSON.parse(bindPopup1)
      .$attrs
      .bindPopup
      .popup
      .primaryButton
      .value, 'confirm')
    assertEqual(JSON.parse(bindPopup1)
      .$attrs
      .bindPopup
      .popup
      .secondaryButton
      .value, 'cancel')

    let button2: Component = await driver.findComponent(Matcher.create().text('confirm').enabled(true))
    await button1.tap()
    let bindPopup2: string = await buttonBindPopup1.getInspectorInfo()
    assertFalse(JSON.parse(bindPopup2).$attrs.bindPopup.show)

    await button2.tap()
    let buttonEnabled1: string = await buttonEnabled.getInspectorInfo()
    assertFalse(JSON.parse(buttonEnabled1).$attrs.enabled)

    await button1.tap()
    let button3: Component = await driver.findComponent(Matcher.create().text('cancel').enabled(true))
    assertFalse(JSON.parse(bindPopup2).$attrs.bindPopup.show)

    await button3.tap()
    let buttonEnabled2: string = await buttonEnabled.getInspectorInfo()
    assertTrue(JSON.parse(buttonEnabled2).$attrs.enabled)
  }, 0)
}