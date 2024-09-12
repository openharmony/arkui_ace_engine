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

export default async function bindPopupTest_seven() {
  /*
   * BindPopup 通用属性
   * 找到画面id为 buttonBindPopup7 的 Button 组件
   * 找到画面文本为 ButtonBindPopup1 ButtonBindPopup2 的 Button 组件
   * 获取 buttonBindPopup7 的 BindPopup.show 属性与期望值 true 比对
   * popup.builder 的属性与期望值 () => {} 比对
   * popup.maskColor 的属性与期望值 0x123abc 比对
   * popup.mask 的属性与期望值 true 比对
   * popup.targetSpace 的属性与期望值 '10px' 比对
   * popup.offset.x 的属性与期望值 1 比对
   * popup.offset.y 的属性与期望值 1 比对
   * 点击 button1 变更 buttonBindPopup7 属性
   * 获取 buttonBindPopup7 的属性
   * BindPopup.show 的属性与期望值 false 比对
   * 点击 button2 变更 buttonBindPopup7 属性
   * 获取 buttonBindPopup7 的属性
   * BindPopup.popup.mask 的属性与期望值 false 比对
   * */
  defineTest('bindPopupTest_sevenDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('bindPopupTest_sevenDemo running')
    let driver: Tester = Tester.create()
    let buttonBindPopup7: Component = await driver.findComponent(Matcher.create().id('buttonBindPopup7').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ButtonBindPopup1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('ButtonBindPopup2').enabled(true))
    let bindPopup1: string = await buttonBindPopup7.getInspectorInfo()
    assertFalse(JSON.parse(bindPopup1).$attrs.bindPopup == undefined)

    assertTrue(JSON.parse(bindPopup1).$attrs.bindPopup.show)
    assertEqual(JSON.parse(bindPopup1)
      .$attrs
      .bindPopup
      .popup
      .builder, () => {
    })
    assertEqual(JSON.parse(bindPopup1)
      .$attrs
      .bindPopup
      .popup
      .maskColor, 0x123abc)
    assertTrue(JSON.parse(bindPopup1)
      .$attrs
      .bindPopup
      .popup
      .mask)
    assertEqual(JSON.parse(bindPopup1)
      .$attrs
      .bindPopup
      .popup
      .targetSpace, '10px')
    assertEqual(JSON.parse(bindPopup1)
      .$attrs
      .bindPopup
      .popup
      .offset
      .x, 1)
    assertEqual(JSON.parse(bindPopup1)
      .$attrs
      .bindPopup
      .popup
      .offset
      .y, 1)
    await button1.tap()
    let bindPopup2: string = await buttonBindPopup7.getInspectorInfo()
    assertFalse(JSON.parse(bindPopup2).$attrs.bindPopup.show)
    await button2.tap()
    let bindPopup3: string = await buttonBindPopup7.getInspectorInfo()
    assertFalse(JSON.parse(bindPopup3)
      .$attrs
      .bindPopup
      .popup
      .mask)
  }, 0)
}