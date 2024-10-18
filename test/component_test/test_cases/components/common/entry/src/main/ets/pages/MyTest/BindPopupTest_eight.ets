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

export default async function bindPopupTest_eight() {
  /*
   * BindPopup 通用属性
   * 找到画面id为 buttonBindPopup8 的 Button 组件
   * 找到画面文本为 ButtonBindPopup 的 Button 组件
   * 获取 buttonBindPopup8 的 bindPopup.show属性与期望值true比对
   * popup.mask.color属性与期望值 Color.Green 比对
   * popup.width属性与期望值 '10px' 比对
   * popup.arrowPointPosition 属性与期望值 ArrowPointPosition.START 比对
   * popup.arrowWidth 属性与期望值 '10px' 比对
   * 点击 button1 变更 buttonBindPopup8 的 bindPopup.show属性为false
   * 获取 bindPopup.show 的属性与期望值 false 比对
   * */
  defineTest('bindPopupTest_eightDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('bindPopupTest_eightDemo running')
    let driver: Tester = Tester.create()
    let buttonBindPopup8: Component = await driver.findComponent(Matcher.create().id('buttonBindPopup8').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ButtonBindPopup').enabled(true))
    let bindPopup1: string = await buttonBindPopup8.getInspectorInfo()
    assertFalse(JSON.parse(bindPopup1).$attrs.bindPopup == undefined)
    assertTrue(JSON.parse(bindPopup1).$attrs.bindPopup.show)
    assertEqual(JSON.parse(bindPopup1)
      .$attrs
      .BindPopup
      .popup
      .mask
      .color, Color.Green)
    assertEqual(JSON.parse(bindPopup1)
      .$attrs
      .BindPopup
      .popup
      .width, '10px')
    assertEqual(JSON.parse(bindPopup1)
      .$attrs
      .BindPopup
      .popup
      .arrowPointPosition, ArrowPointPosition.START)
    assertEqual(JSON.parse(bindPopup1)
      .$attrs
      .BindPopup
      .popup
      .arrowWidth, '10px')
    await button1.tap()
    let bindPopup2: string = await buttonBindPopup8.getInspectorInfo()
    assertFalse(JSON.parse(bindPopup2).$attrs.BindPopup.show)
  }, 0)
}