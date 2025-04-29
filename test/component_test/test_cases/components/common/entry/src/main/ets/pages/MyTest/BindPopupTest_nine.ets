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

export default async function bindPopupTest_nine() {
  /*
   * BindPopup 通用属性
   * 找到画面id为 buttonBindPopup9 的 Button 组件
   * 找到画面文本为 ButtonBindPopup1 ButtonBindPopup2 的 Button 组件
   * 获取 buttonBindPopup9 的 BindPopup.show 属性与期望值 true 比对
   * popup.mask.color 的属性与期望值 Color.Green 比对
   * popup.arrowHeight 的属性与期望值 '10px' 比对
   * popup.radius 的属性与期望值 '10px' 比对
   * popup.shadow 的属性与期望值 ShadowStyle.OUTER_DEFAULT_XS 比对
   * popup.backgroundBlurStyle 的属性与期望值 BlurStyle.BACKGROUND_REGULAR 比对
   * popup.focusable 的属性与期望值 true 比对
   * 点击 button1 变更 buttonBindPopup9 属性
   * 获取 buttonBindPopup9 的属性
   * BindPopup.show 的属性与期望值 false 比对
   * popup.fill 的属性与期望值 true 比对
   * 点击 button2 变更 buttonBindPopup9 的属性
   * 获取 buttonBindPopup9 的属性
   * popup.focusable 的属性与期望值 ShadowType.COLOR 比对
   * popup.radius 的属性与期望值 10 比对
   * popup.type 的属性与期望值 ShadowType.COLOR 比对
   * popup.color 的属性与期望值 Color.Blue 比对
   * popup.offsetX 的属性与期望值 1 比对
   * popup.offsetY 的属性与期望值 1 比对
   * popup.fill 的属性与期望值 true 比对
   * */
  defineTest('bindPopupTest_nineDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('bindPopupTest_nineDemo running')
    let driver: Tester = Tester.create()
    let buttonBindPopup9: Component = await driver.findComponent(Matcher.create().id('buttonBindPopup9').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ButtonBindPopup1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('ButtonBindPopup2').enabled(true))
    let bindPopup1: string = await buttonBindPopup9.getInspectorInfo()
    assertFalse(JSON.parse(bindPopup1).$attrs.BindPopup == undefined)
    assertTrue(JSON.parse(bindPopup1).$attrs.BindPopup.show)
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
      .arrowHeight, '10px')
    assertEqual(JSON.parse(bindPopup1)
      .$attrs
      .BindPopup
      .popup
      .radius, '10px')
    assertEqual(JSON.parse(bindPopup1)
      .$attrs
      .BindPopup
      .popup
      .shadow, ShadowStyle.OUTER_DEFAULT_XS)
    assertEqual(JSON.parse(bindPopup1)
      .$attrs
      .BindPopup
      .popup
      .backgroundBlurStyle, BlurStyle.BACKGROUND_REGULAR)
    assertTrue(JSON.parse(bindPopup1)
      .$attrs
      .BindPopup
      .popup
      .focusable)

    await button1.tap()
    let bindPopup2: string = await buttonBindPopup9.getInspectorInfo()
    assertFalse(JSON.parse(bindPopup2).$attrs.BindPopup.show)

    await button2.tap()
    let bindPopup3: string = await buttonBindPopup9.getInspectorInfo()
    assertFalse(JSON.parse(bindPopup3)
      .$attrs
      .BindPopup
      .popup
      .focusable)
    assertEqual(JSON.parse(bindPopup3)
      .$attrs
      .BindPopup
      .popup
      .shadow
      .radius, 10)
    assertEqual(JSON.parse(bindPopup3)
      .$attrs
      .BindPopup
      .popup
      .shadow
      .type, ShadowType.COLOR)
    assertEqual(JSON.parse(bindPopup3)
      .$attrs
      .BindPopup
      .popup
      .shadow
      .color, Color.Blue)
    assertEqual(JSON.parse(bindPopup3)
      .$attrs
      .BindPopup
      .popup
      .shadow
      .offsetX, 1)
    assertEqual(JSON.parse(bindPopup3)
      .$attrs
      .BindPopup
      .popup
      .shadow
      .offsetY, 1)
    assertTrue(JSON.parse(bindPopup3)
      .$attrs
      .BindPopup
      .popup
      .shadow
      .fill)
  }, 0)
}