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

export default async function bindSheetTest_one() {
  /*
   * bindSheet 通用属性
   * 找到画面id为 buttonBindSheet1 buttonBindSheet2 的 Button 组件
   * 找到画面文本为 ButtonBindSheet1 ButtonBindSheet2 的按钮
   * 获取 buttonBindSheet1 的属性(isShow builder height detents shouldDismiss showClose dragBar)
   * 获取 buttonBindSheet2 的属性(isShow builder height )
   * 将获取到的值与期望值比对
   * 点击 button1 变更 Button1 Button2 的属性
   * 获取 buttonBindSheet1 的属性(isShow height)
   * 获取 buttonBindSheet2 的属性(isShow height detents)
   * 将获取到的值与期望值比对
   * 点击 button2 变更 Button1 Button2 的 height 属性
   * 获取 buttonBindSheet1 的属性与期望值 $r("app.string.common_value_two")
   * 获取 buttonBindSheet2 的属性与期望值 SheetSize.FIT_CONTENT 比对
   * */
  defineTest('bindSheetTest_oneDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('bindSheetTest_oneDemo running')
    let driver: Tester = Tester.create()
    let buttonBindSheet1: Component = await driver.findComponent(Matcher.create().id('buttonBindSheet1').enabled(true))
    let buttonBindSheet2: Component = await driver.findComponent(Matcher.create().id('buttonBindSheet2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ButtonBindSheet1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('ButtonBindSheet2').enabled(true))
    let myBuilder: Component = await driver.findComponent(Matcher.create().text('myBuilder').enabled(true))
    let bindPopupBuilder: string = await myBuilder.getType()
    assertEqual(bindPopupBuilder, 'Button')
    let bindSheet1: string = await buttonBindSheet1.getInspectorInfo()
    assertFalse(JSON.parse(bindSheet1).$attrs.bindSheet == undefined)
    assertTrue(JSON.parse(bindSheet1).$attrs.bindSheet.isShow)
    assertEqual(JSON.parse(bindSheet1)
      .$attrs
      .bindSheet
      .options
      .height, '100')
    assertEqual(JSON.parse(bindSheet1)
      .$attrs
      .bindSheet
      .options
      .detents, [SheetSize.MEDIUM, SheetSize.LARGE, SheetSize.FIT_CONTENT])
    assertTrue(JSON.parse(bindSheet1)
      .$attrs
      .bindSheet
      .options
      .showClose)
    assertTrue(JSON.parse(bindSheet1)
      .$attrs
      .bindSheet
      .options
      .dragBar)

    let bindSheet2: string = await buttonBindSheet2.getInspectorInfo()
    assertTrue(JSON.parse(bindSheet2).$attrs.bindSheet.isShow)
    assertEqual(JSON.parse(bindSheet2)
      .$attrs
      .bindSheet
      .options
      .height, SheetSize.MEDIUM)

    await button1.tap()
    let bindSheet3: string = await buttonBindSheet1.getInspectorInfo()
    let bindSheet4: string = await buttonBindSheet2.getInspectorInfo()
    assertFalse(JSON.parse(bindSheet3).$attrs.bindSheet.isShow)
    assertFalse(JSON.parse(bindSheet4).$attrs.bindSheet.isShow)
    assertEqual(JSON.parse(bindSheet3)
      .$attrs
      .bindSheet
      .options
      .height, 100)
    assertEqual(JSON.parse(bindSheet4)
      .$attrs
      .bindSheet
      .options
      .height, SheetSize.LARGE)
    assertEqual(JSON.parse(bindSheet4)
      .$attrs
      .bindSheet
      .options
      .detents, [100, '100', $r("app.string.common_value_two")])
    await button2.tap()
    let bindSheet5: string = await buttonBindSheet1.getInspectorInfo()
    let bindSheet6: string = await buttonBindSheet2.getInspectorInfo()
    assertEqual(JSON.parse(bindSheet5)
      .$attrs
      .bindSheet
      .options
      .height, $r("app.string.common_value_two"))
    assertEqual(JSON.parse(bindSheet6)
      .$attrs
      .bindSheet
      .options
      .height, SheetSize.FIT_CONTENT)
  }, 0)
}