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

import { assertEqual, assertFalse, assertTrue } from '@ohos.arkui.componentTest';
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'
import { logLibrary } from '@kit.PerformanceAnalysisKit';

export default async function shadowTest_one() {
  /*
   * CalendarPicker组件 shadow通用属性
   * 找到画面id为 calendarPicker1 calendarPicker2 的 CalendarPicker 组件
   * 找到画面文本为 ButtonShadow1 ButtonShadow2 ButtonShadow3 ButtonShadow4 ButtonShadow5 的 Button 组件
   * 获取 calendarPicker2 的属性
   * radius 与期望值 50.000000 比对
   * type 与期望值 ShadowType.BLUR 比对
   * color 与期望值 #FFF12525) 比对
   * offsetX 与期望值 $r("app.string.any_offset") 比对
   * offsetY 与期望值 $r("app.string.any_offset") 比对
   * fill 与期望值 1
   * 获取 calendarPicker1 的属性
   * radius 与期望值 20.000000 比对
   * type 与期望值 ShadowType.COLOR 比对
   * color 与期望值 #FF0000FF 比对
   * offsetX 与期望值 50.000000 比对
   * offsetY 与期望值 50.000000 比对
   * fill 与期望值 0
   * 点击button1切换calendarPicker1的属性
   * radius与期望值 $r('app.string.any_offset') 比对
   * color与期望值 $r('app.color.start_window_background') 比对
   * offsetX与期望值 $r("app.string.any_offset") 比对
   * offsetY与期望值 $r("app.string.any_offset") 比对
   * 点击button2切换calendarPicker1的属性
   * color与期望值背景色相反色'#FF000000'; 比对
   * 点击button3切换calendarPicker1的属性
   * color与期望值 ColoringStrategy.AVERAGE 比对
   * 点击button4切换calendarPicker1的属性
   * color与期望值 ColoringStrategy.PRIMARY 比对
   * 点击button4切换calendarPicker1的属性
   * color与期望值 #FF0000FF 比对
   * */
  defineTest('ShadowTest_one', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("ShadowTest_one running")
    let driver: Tester = Tester.create()
    let calendarPicker1: Component = await driver.findComponent(Matcher.create().id('calendarPicker1').enabled(true))
    let calendarPicker2: Component = await driver.findComponent(Matcher.create().id('calendarPicker2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ButtonShadow1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('ButtonShadow2').enabled(true))
    let button3: Component = await driver.findComponent(Matcher.create().text('ButtonShadow3').enabled(true))
    let button4: Component = await driver.findComponent(Matcher.create().text('ButtonShadow4').enabled(true))
    let button5: Component = await driver.findComponent(Matcher.create().text('ButtonShadow5').enabled(true))
    let shadow1: string = await calendarPicker2.getInspectorInfo()
    assertEqual(JSON.parse(shadow1)
      .$attrs
      .shadow
      .radius, '50.000000')
    assertTrue(JSON.parse(shadow1)
      .$attrs
      .shadow
      .type == ShadowType.BLUR)
    assertEqual(JSON.parse(shadow1)
      .$attrs
      .shadow
      .color, "#FFF12525")
    assertEqual(JSON.parse(shadow1)
      .$attrs
      .shadow
      .offsetX, $r("app.string.any_offset"))
    assertEqual(JSON.parse(shadow1)
      .$attrs
      .shadow
      .offsetY, $r("app.string.any_offset"))
    assertTrue(JSON.parse(shadow1).$attrs.shadow.fill == 1)
    let shadow2: string = await calendarPicker1.getInspectorInfo()
    assertEqual(JSON.parse(shadow2)
      .$attrs
      .shadow
      .radius, '20.000000')
    assertTrue(JSON.parse(shadow2)
      .$attrs
      .shadow
      .type == ShadowType.COLOR)
    assertEqual(JSON.parse(shadow2)
      .$attrs
      .shadow
      .color, '#FF0000FF')
    assertEqual(JSON.parse(shadow2)
      .$attrs
      .shadow
      .offsetX, '50.000000')
    assertEqual(JSON.parse(shadow2)
      .$attrs
      .shadow
      .offsetY, '50.000000')
    assertTrue(JSON.parse(shadow2).$attrs.shadow.fill == 0)
    await button1.tap()
    let shadow3: string = await calendarPicker1.getInspectorInfo()
    assertEqual(JSON.parse(shadow3)
      .$attrs
      .shadow
      .color, $r('app.color.start_window_background'))
    assertEqual(JSON.parse(shadow3)
      .$attrs
      .shadow
      .radius, $r('app.string.any_offset'))
    assertEqual(JSON.parse(shadow3)
      .$attrs
      .shadow
      .offsetX, $r("app.string.any_offset"))
    assertEqual(JSON.parse(shadow3)
      .$attrs
      .shadow
      .offsetY, $r("app.string.any_offset"))
    await button2.tap()
    let shadow4: string = await calendarPicker1.getInspectorInfo()
    assertTrue(JSON.parse(shadow4)
      .$attrs
      .shadow
      .color == '#FF000000')
    await button3.tap()
    let shadow5: string = await calendarPicker1.getInspectorInfo()
    assertTrue(JSON.parse(shadow5)
      .$attrs
      .shadow
      .color == 'ColoringStrategy.AVERAGE')
    await button4.tap()
    let shadow6: string = await calendarPicker1.getInspectorInfo()
    assertTrue(JSON.parse(shadow6)
      .$attrs
      .shadow
      .color == 'ColoringStrategy.PRIMARY')
    await button5.tap()
    let shadow7: string = await calendarPicker1.getInspectorInfo()
    assertEqual(JSON.parse(shadow7)
      .$attrs
      .shadow
      .color, '#FF0000FF')
  }, 0)
}