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
import { assertEqual, assertFalse } from '@ohos.arkui.componentTest'
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'

export default async function progressMaskTest() {
  /*
   * Image组件 ProgressMask通用属性
   * 找到画面id为imageProgressMask的组件
   * 找到画面text为ButtonProgressMask的button组件
   * 获取imageProgressMask的progressMask属性与期待值{ value: 10.0, total: 100.0, color: 'rgb(72 61 139)' } 比较
   * 点击button，变更imageProgressMask的progressMask属性为{ value: 10.0, total: 100.0, color: 0X528B8B }
   * 获取imageProgressMask的progressMask属性与期待值{ value: 10.0, total: 100.0, color: 0X528B8B }比较
   * 点击button，变更imageProgressMask的progressMask属性为{ value: 10.0, total: 100.0, color: Color.Red }
   * 获取imageProgressMask的progressMask属性与期待值{ value: 10.0, total: 100.0, color: Color.Red }比较
   * 点击button，变更imageProgressMask的progressMask属性为{ value: 10.0, total: 100.0, color: $r('sys.color.ohos_id_color_text_hyperlink') }
   * 获取imageProgressMask的progressMask属性中的color与期待值{ value: 10.0, total: 100.0, color: $r('sys.color.ohos_id_color_text_hyperlink') }比较
   */
  defineTest('progressMaskTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('progressMaskTestDemo running')
    let driver: Tester = Tester.create()
    let imageProgressMask: Component =
      await driver.findComponent(Matcher.create().id('imageProgressMask').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ButtonProgressMask').enabled(true))
    let progressMask1: string = await imageProgressMask.getInspectorInfo()
    assertFalse(JSON.parse(progressMask1)
      .$attrs
      .value == undefined)
    assertEqual(JSON.parse(progressMask1)
      .$attrs
      .value, 10.0)
    assertEqual(JSON.parse(progressMask1)
      .$attrs
      .total, 100.0)
    assertEqual(JSON.parse(progressMask1)
      .$attrs
      .color, 'rgb(72 61 139)')

    await button.tap()
    let progressMask2: string = await imageProgressMask.getInspectorInfo()
    assertEqual(JSON.parse(progressMask2)
      .$attrs
      .value, 10.0)
    assertEqual(JSON.parse(progressMask2)
      .$attrs
      .total, 100.0)
    assertEqual(JSON.parse(progressMask2)
      .$attrs
      .color, 0X528B8B)

    let progressMask3: string = await imageProgressMask.getInspectorInfo()
    assertEqual(JSON.parse(progressMask3)
      .$attrs
      .value, 10.0)
    assertEqual(JSON.parse(progressMask3)
      .$attrs
      .total, 100.0)
    assertEqual(JSON.parse(progressMask3)
      .$attrs
      .color, Color.Red)

    await button.tap()
    let progressMask4: string = await imageProgressMask.getInspectorInfo()
    assertEqual(JSON.parse(progressMask4)
      .$attrs
      .value, 10.0)
    assertEqual(JSON.parse(progressMask4)
      .$attrs
      .total, 100.0)
    assertEqual(JSON.parse(progressMask4)
      .$attrs
      .color, $r('sys.color.ohos_id_color_text_hyperlink'))
  }, 0)
}