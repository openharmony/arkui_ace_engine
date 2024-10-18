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

export default async function bindPopupTest_four() {
  /*
   * BindPopup 通用属性
   * 找到画面id为 buttonBindPopup4 的 Button 组件
   * 找到画面文本为 ButtonBindPopup2 的 Button 组件
   * 获取 buttonBindPopup4 的 BindPopup.show 属性与期望值 true 比对
   * popup.message 属性与期望值 "bindPopup" 比对
   * popup.radius 属性与期望值 '30px' 比对
   * popup.shadow 属性与期望值 ShadowStyle.OUTER_DEFAULT_XS 比对
   * popup.backgroundBlurStyle 属性与期望值 '100px' 比对
   * popup.arrowHeight 属性与期望值 "bindPopup" 比对
   * 点击 button1 变更 buttonBindPopup4 的BindPopup.show属性为false
   * 获取 BindPopup.show 的属性与期望值 false 比对
   * 点击 button2 变更 buttonBindPopup4 的popup.enableArrow 和 popup.autoCancel 属性 为 false
   * popup.radius 的属性与期望值 10 比对
   * popup.type 的属性与期望值 ShadowType.COLOR 比对
   * popup.color 的属性与期望值 Color.Blue 比对
   * popup.offsetX 的属性与期望值 1 比对
   * popup.offsetY 的属性与期望值 1 比对
   * popup.fill 的属性与期望值 true 比对
   * */
  defineTest('bindPopupTest_fourDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('bindPopupTest_fourDemo running')
    let driver: Tester = Tester.create()
    let buttonBindPopup4: Component = await driver.findComponent(Matcher.create().id('buttonBindPopup4').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ButtonBindPopup2').enabled(true))
    let bindPopup1: string = await buttonBindPopup4.getInspectorInfo()
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
      .radius, '30px')
    assertEqual(JSON.parse(bindPopup1)
      .$attrs
      .bindPopup
      .popup
      .shadow, ShadowStyle.OUTER_DEFAULT_XS)
    assertEqual(JSON.parse(bindPopup1)
      .$attrs
      .bindPopup
      .popup
      .backgroundBlurStyle, '100px')
    assertEqual(JSON.parse(bindPopup1)
      .$attrs
      .bindPopup
      .popup
      .arrowHeight, "bindPopup")
    await buttonBindPopup4.tap()
    let bindPopup2: string = await buttonBindPopup4.getInspectorInfo()
    assertFalse(JSON.parse(bindPopup2).$attrs.bindPopup.show)
    await button1.tap()
    let bindPopup3: string = await buttonBindPopup4.getInspectorInfo()
    assertEqual(JSON.parse(bindPopup3)
      .$attrs
      .bindPopup
      .popup
      .shadow
      .radius, 10)
    assertEqual(JSON.parse(bindPopup3)
      .$attrs
      .bindPopup
      .popup
      .shadow
      .type, ShadowType.COLOR)
    assertEqual(JSON.parse(bindPopup3)
      .$attrs
      .bindPopup
      .popup
      .shadow
      .color, Color.Blue)
    assertEqual(JSON.parse(bindPopup3)
      .$attrs
      .bindPopup
      .popup
      .shadow
      .offsetX, 1)
    assertEqual(JSON.parse(bindPopup3)
      .$attrs
      .bindPopup
      .popup
      .shadow
      .offsetY, 1)
    assertTrue(JSON.parse(bindPopup3)
      .$attrs
      .bindPopup
      .popup
      .shadow
      .fill)
  }, 0)
}