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

export default async function bindPopupTest_two() {
  /*
   * BindPopup 通用属性
   * 找到画面id为 buttonBindPopup3 的 Button 组件
   * 找到画面文本为 ButtonBindPopup 的 Button 组件
   * 获取 buttonBindPopup7 的 BindPopup.show 属性与期望值 true 比对
   * popup.message 的属性与期望值 "bindPopup" 比对
   * popup.arrowOffset 的属性与期望值 1 比对
   * popup.showInSubWindow 的属性与期望值 true 比对
   * popup.mask 的属性与期望值 true 比对
   * popup.messageOptions.textColor 的属性与期望值 Color.Blue 比对
   * popup.messageOptions.font.size 的属性与期望值 10 比对
   * popup.messageOptions.font.weight 的属性与期望值 '5' 比对
   * 点击 button1 变更 buttonBindPopup7 属性
   * 获取 buttonBindPopup7 的属性
   * BindPopup.show 的属性与期望值 false 比对
   * */
  defineTest('bindPopupTest_twoDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('bindPopupTest_twoDemo running')
    let driver: Tester = Tester.create()
    let buttonBindPopup2: Component = await driver.findComponent(Matcher.create().id('buttonBindPopup2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ButtonBindPopup').enabled(true))
    let bindPopup1: string = await buttonBindPopup2.getInspectorInfo()
    assertFalse(JSON.parse(bindPopup1).$attrs.bindPopup == undefined)
    assertTrue(JSON.parse(bindPopup1).$attrs.bindPopup.show)
    assertEqual(JSON.parse(bindPopup1)
      .$attrs
      .bindPopup
      .popup
      .message, "bindPopup")
    assertEqual(JSON.parse(bindPopup1)
      .$attrs
      .bindPopup
      .popup
      .arrowOffset, 1)
    assertTrue(JSON.parse(bindPopup1)
      .$attrs
      .bindPopup
      .popup
      .showInSubWindow)
    assertTrue(JSON.parse(bindPopup1)
      .$attrs
      .bindPopup
      .popup
      .mask)
    assertEqual(JSON.parse(bindPopup1)
      .$attrs
      .bindPopup
      .popup
      .messageOptions
      .textColor, Color.Blue)
    assertEqual(JSON.parse(bindPopup1)
      .$attrs
      .bindPopup
      .popup
      .messageOptions
      .font
      .size, 10)
    assertEqual(JSON.parse(bindPopup1)
      .$attrs
      .bindPopup
      .popup
      .messageOptions
      .font
      .weight, '5')
    await button1.tap()
    let bindPopup2: string = await buttonBindPopup2.getInspectorInfo()
    assertFalse(JSON.parse(bindPopup2).$attrs.bindPopup.show)
  }, 0)
}