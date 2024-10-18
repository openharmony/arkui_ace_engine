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

export default async function bindPopupTest_three() {
  /*
   * BindPopup 通用属性
   * 找到画面id为 buttonBindPopup3 的 Button 组件
   * 找到画面文本为 ButtonBindPopup 的 Button 组件
   * 获取 Button1 的 BindPopup.show 属性与期望值 true 比对
   * popup.message 的属性与期望值 "bindPopup" 比对
   * popup.targetSpace 的属性与期望值 $r('app.string.CommonValue1') 比对
   * popup.offset.x 的属性与期望值 1 比对
   * popup.offset.y 的属性与期望值 1 比对
   * popup.width 的属性与期望值 '100px' 比对
   * popup.arrowWidth 的属性与期望值 '10px' 比对
   * 点击 button1 变更 Button1 属性
   * 获取Button1的属性
   * BindPopup.show 的属性与期望值 false 比对
   * */
  defineTest('bindPopupTest_threeDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('bindPopupTest_threeDemo running')
    let driver: Tester = Tester.create()
    let buttonBindPopup3: Component = await driver.findComponent(Matcher.create().id('buttonBindPopup3').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ButtonBindPopup').enabled(true))
    let bindPopup1: string = await buttonBindPopup3.getInspectorInfo()
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
      .targetSpace, $r("app.string.common_value_one"))
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
    assertEqual(JSON.parse(bindPopup1)
      .$attrs
      .bindPopup
      .popup
      .width, '100px')
    assertEqual(JSON.parse(bindPopup1)
      .$attrs
      .bindPopup
      .popup
      .arrowWidth, '10px')
    await button1.tap()
    let bindPopup3: string = await buttonBindPopup3.getInspectorInfo()
    assertFalse(JSON.parse(bindPopup3).$attrs.bindPopup.show)
  }, 0)
}