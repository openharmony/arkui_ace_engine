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

export default async function textPickerSelectedIndexTest() {
  /*
   * TextPicker组件 SelectedIndex属性
   * 找到画面id为textPickerSelectedIndex1，textPickerSelectedIndex2，textPickerSelectedIndex3的TextPicker组件
   * 找到画面文本为TextPickerSelectedIndex的Button组件
   * 获取textPickerSelectedIndex1的SelectedIndex属性与期待值2比对
   * 获取textPickerSelectedIndex2的SelectedIndex属性与期待值[3, 0]比对
   * 点击button，变更textPickerSelectedIndex2的SelectedIndex属性值为[2, 0]
   * 获取textPickerSelectedIndex2的SelectedIndex属性与期待值[2, 0]比对
   */
  defineTest('textPickerSelectedIndexTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('textPickerSelectedIndexTestDemo running')
    let driver: Tester = Tester.create()
    let textPickerSelectedIndex1: Component =
      await driver.findComponent(Matcher.create().id('textPickerSelectedIndex1').enabled(true))
    let textPickerSelectedIndex2: Component =
      await driver.findComponent(Matcher.create().id('textPickerSelectedIndex2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('TextPickerSelectedIndex').enabled(true))

    let selectedIndex1: string = await textPickerSelectedIndex1.getInspectorInfo()
    assertEqual(JSON.parse(selectedIndex1).$attrs.selectedIndex, 2)

    let selectedIndex2: string = await textPickerSelectedIndex2.getInspectorInfo()
    assertEqual(JSON.parse(selectedIndex2).$attrs.selectedIndex, [3, 0])

    await button.tap()
    let selectedIndex3: string = await textPickerSelectedIndex2.getInspectorInfo()
    assertEqual(JSON.parse(selectedIndex3).$attrs.selectedIndex, [2, 0])
  }, 0)
}