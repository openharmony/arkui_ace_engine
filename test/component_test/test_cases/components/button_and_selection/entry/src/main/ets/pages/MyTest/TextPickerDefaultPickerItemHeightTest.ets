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

export default async function textPickerDefaultPickerItemHeightTest() {
  /*
   * TextPicker组件 DefaultPickerItemHeight属性
   * 找到画面id为textPickerDefaultPickerItemHeight的TextPicker组件
   * 找到画面文本为TextPickerDefaultPickerItemHeight的Button组件
   * 获取textPickerDefaultPickerItemHeight的DefaultPickerItemHeight属性与期待值'100.00fp'比对
   * 点击button，变更textPickerDefaultPickerItemHeight的DefaultPickerItemHeight属性值为'50.00px'
   * 获取textPickerDefaultPickerItemHeight的DefaultPickerItemHeight属性与期待值'50.00px'比对
   */
  defineTest('textPickerDefaultPickerItemHeightTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('textPickerDefaultPickerItemHeightTestDemo running')
    let driver: Tester = Tester.create()
    let textPickerDefaultPickerItemHeight: Component =
      await driver.findComponent(Matcher.create().id('textPickerDefaultPickerItemHeight').enabled(true))
    let button: Component =
      await driver.findComponent(Matcher.create().text('TextPickerDefaultPickerItemHeight').enabled(true))

    let defaultPickerItemHeight1: string = await textPickerDefaultPickerItemHeight.getInspectorInfo()
    assertEqual(JSON.parse(defaultPickerItemHeight1).$attrs.defaultPickerItemHeight, '100.00fp')

    await button.tap()
    let defaultPickerItemHeight2: string = await textPickerDefaultPickerItemHeight.getInspectorInfo()
    assertEqual(JSON.parse(defaultPickerItemHeight2).$attrs.defaultPickerItemHeight, '50.00px')
  }, 0)
}