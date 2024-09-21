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
import { logLibrary } from '@kit.PerformanceAnalysisKit'

export default async function bindSheetTest_three() {
  /*
* bindSheet 通用属性
* 找到画面id为 buttonBindSheet5 buttonBindSheet6 textBindSheet7 的 Button、 Text 组件
* 找到画面文本为 ButtonBindSheet 的 Button 组件 命名为 button1
* 获取 buttonBindSheet5 buttonBindSheet6 textBindSheet7 的属性
* 并命名为 bindSheet5 bindSheet6 bindSheet7
* bindSheet5 的 isShow 属性和期望值 true 比对
* bindSheet5 的 maskColor 属性和期望值 $r("app.string.common_color") 比对
* bindSheet5 的 title 属性和期望值 "title" 比对
* bindSheet5 的 subtitle 属性和期望值 "subtitle" 比对
* bindSheet5 的 enableOutsideInteractive 属性和期望值 true 比对
* bindSheet6 的 title 属性和期望值 $r('app.string.module_desc') 比对
* bindSheet6 的 subtitle 属性和期望值 $r('app.string.module_desc') 比对
* bindSheet7 的 isShow 属性和期望值 false 比对
* bindSheet7 的 maskColor 属性和期望值 'rgb(192,124,3)' 比对
* 点击 button1 切换属性
* 获取 buttonBindSheet5 textBindSheet7 的属性
* 并命名为 bindSheet8 bindPopup5
* bindSheet8 的 enableOutsideInteractive 属性和期望值 false 比对
* bindSheet8 的 maskColor 属性和期望值 Color.Black 比对
* bindPopup5 的 maskColor 属性和期望值 0x77fa6e 比对
*/
  defineTest('bindSheetTest_threeDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('bindSheetTest_threeDemo running')
    let driver: Tester = Tester.create()
    let buttonBindSheet5: Component = await driver.findComponent(Matcher.create().id('buttonBindSheet5').enabled(true))
    let buttonBindSheet6: Component = await driver.findComponent(Matcher.create().id('buttonBindSheet6').enabled(true))
    let textBindSheet7: Component = await driver.findComponent(Matcher.create().id('textBindSheet7').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ButtonBindSheet').enabled(true))
    let bindSheet5: string = await buttonBindSheet5.getInspectorInfo()
    let bindSheet6: string = await buttonBindSheet6.getInspectorInfo()
    let bindSheet7: string = await textBindSheet7.getInspectorInfo()
    assertFalse(JSON.parse(bindSheet5).$attrs.bindSheet == undefined)
    assertTrue(JSON.parse(bindSheet5).$attrs.bindSheet.isShow)
    assertEqual(JSON.parse(bindSheet5)
      .$attrs
      .bindSheet
      .option
      .maskColor, $r("app.string.common_color"))
    assertEqual(JSON.parse(bindSheet5)
      .$attrs
      .bindSheet
      .option
      .title
      .title, "title")
    assertEqual(JSON.parse(bindSheet5)
      .$attrs
      .bindSheet
      .option
      .title
      .subtitle, "subtitle")
    assertTrue(JSON.parse(bindSheet5)
      .$attrs
      .bindSheet
      .option
      .enableOutsideInteractive)
    assertEqual(JSON.parse(bindSheet6)
      .$attrs
      .bindSheet
      .option
      .title
      .title, $r('app.string.module_desc'))
    assertEqual(JSON.parse(bindSheet6)
      .$attrs
      .bindSheet
      .option
      .title
      .subtitle, $r('app.string.module_desc'))
    assertFalse(JSON.parse(bindSheet7).$attrs.bindSheet.isShow)
    assertEqual(JSON.parse(bindSheet7)
      .$attrs
      .bindSheet
      .options
      .maskColor, 'rgb(192,124,3)')
    await button1.tap()
    let bindSheet8: string = await buttonBindSheet5.getInspectorInfo()
    let bindPopup5: string = await textBindSheet7.getInspectorInfo()
    assertFalse(JSON.parse(bindSheet8)
      .$attrs
      .bindSheet
      .option
      .enableOutsideInteractive)
    assertEqual(JSON.parse(bindSheet8)
      .$attrs
      .bindSheet
      .option
      .maskColor, Color.Black)
    assertEqual(JSON.parse(bindPopup5)
      .$attrs
      .bindSheet
      .options
      .maskColor, 0x77fa6e)
  }, 0)
}