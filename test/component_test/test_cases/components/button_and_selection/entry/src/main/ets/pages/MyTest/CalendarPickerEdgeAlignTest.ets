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

import { assertEqual, Component, defineTest, Matcher, TestCaseLevel, Tester } from '@ohos.arkui.componentTest'

export default async function calendarPickerEdgeAlignTest() {
  /*
   * CalendarPicker组件 EdgeAlign属性
   * 找到画面id为calendarPickerEdgeAlign1，calendarPickerEdgeAlign2的CalendarPicker组件
   * 找到画面文本为CalendarPickerEdgeAlign的Button组件
   * 获取calendarPickerEdgeAlign1的EdgeAlign属性与期待值CalendarAlign.START, {dx: '10.00px', dy:'10.00px'}比对
   * 获取calendarPickerEdgeAlign2的EdgeAlign属性与期待值CalendarAlign.CENTER, {dx: '50.00vp', dy: '50.00vp'}比对
   * 点击button，变更calendarPickerEdgeAlign2的EdgeAlign属性值为CalendarAlign.END, {dx: $r('app.string.picker_edgeOffset'), dy: $r('app.string.picker_edgeOffset')}
   * 获取calendarPickerEdgeAlign2的EdgeAlign属性与期待值CalendarAlign.END, {dx: $r('app.string.picker_edgeOffset'), dy: $r('app.string.picker_edgeOffset')}比对
   */
  defineTest('calendarPickerEdgeAlignTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('calendarPickerEdgeAlignTestDemo running')
    let driver: Tester = Tester.create()
    let calendarPickerEdgeAlign1: Component =
      await driver.findComponent(Matcher.create().id('calendarPickerEdgeAlign1').enabled(true))
    let calendarPickerEdgeAlign2: Component =
      await driver.findComponent(Matcher.create().id('calendarPickerEdgeAlign2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('CalendarPickerEdgeAlign').enabled(true))

    let edgeAlign1: string = await calendarPickerEdgeAlign1.getInspectorInfo()
    assertEqual(JSON.parse(edgeAlign1).$attrs.edgeAlign.alignType, 'CalendarAlign.START')
    assertEqual(JSON.parse(edgeAlign1)
      .$attrs
      .edgeAlign
      .offset
      .dx, '10.00px')
    assertEqual(JSON.parse(edgeAlign1)
      .$attrs
      .edgeAlign
      .offset
      .dy, '10.00px')

    let edgeAlign2: string = await calendarPickerEdgeAlign2.getInspectorInfo()
    assertEqual(JSON.parse(edgeAlign2).$attrs.edgeAlign.alignType, 'CalendarAlign.CENTER')
    assertEqual(JSON.parse(edgeAlign2)
      .$attrs
      .edgeAlign
      .offset
      .dx, '50.00vp')
    assertEqual(JSON.parse(edgeAlign2)
      .$attrs
      .edgeAlign
      .offset
      .dy, '50.00vp')

    await button.tap()
    let edgeAlign3: string = await calendarPickerEdgeAlign2.getInspectorInfo()
    assertEqual(JSON.parse(edgeAlign3).$attrs.edgeAlign.alignType, 'CalendarAlign.END')
    assertEqual(JSON.parse(edgeAlign3)
      .$attrs
      .edgeAlign
      .offset
      .dx, $r('app.string.picker_edgeOffset'))
    assertEqual(JSON.parse(edgeAlign3)
      .$attrs
      .edgeAlign
      .offset
      .dy, $r('app.string.picker_edgeOffset'))
  }, 0)
}