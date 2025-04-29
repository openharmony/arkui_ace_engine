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
import { assertTrue, assertFalse } from '@ohos.arkui.componentTest'
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'

export default async function defaultFocusTest() {
  /*
  * 使用 Checkbox组件 DefaultFocus属性
  * 找到画面id为checkboxDefaultFocus的Checkbox组件
  * 找到画面文本为ButtonDefaultFocus的Button组件
  * 获取checkboxDefaultFocus的DefaultFocus属性与期待值false比对
  * 点击button，变更checkboxDefaultFocus的DefaultFocus属性值为true
  * 获取checkboxDefaultFocus的DefaultFocus属性与期待值true比对
  */
  defineTest('defaultFocusTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('defaultFocusTestDemo running')
    let driver: Tester = Tester.create()
    let checkboxDefaultFocus: Component =
      await driver.findComponent(Matcher.create().id('checkboxDefaultFocus').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ButtonDefaultFocus').enabled(true))
    let defaultFocus1: string = await checkboxDefaultFocus.getInspectorInfo()
    assertFalse(JSON.parse(defaultFocus1).$attrs.defaultFocus)
    await button.tap()

    let defaultFocus2: string = await checkboxDefaultFocus.getInspectorInfo()
    assertTrue(JSON.parse(defaultFocus2).$attrs.defaultFocus)
  }, 0)
}