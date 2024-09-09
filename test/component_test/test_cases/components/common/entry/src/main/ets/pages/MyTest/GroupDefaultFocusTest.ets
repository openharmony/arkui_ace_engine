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

export default async function groupDefaultFocusTest() {
  /*
  * 使用Checkbox组件 GroupDefaultFocus属性
  * 找到画面id为checkboxGroupDefaultFocus的 checkbox 组件
  * 找到画面文本为ButtonGroupDefaultFocus的Button组件
  * 获取checkboxGroupDefaultFocus的GroupDefaultFocus属性与期待值true比对
  * 点击button，变更checkboxGroupDefaultFocus的GroupDefaultFocus属性值为false
  * 获取checkboxGroupDefaultFocus的GroupDefaultFocus属性与期待值false比对
  */
  defineTest('groupDefaultFocusTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('groupDefaultFocusTestDemo running')
    let driver: Tester = Tester.create()
    let checkboxGroupDefaultFocus: Component =
      await driver.findComponent(Matcher.create().id('checkboxGroupDefaultFocus').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ButtonGroupDefaultFocus').enabled(true))
    let groupDefaultFocus1: string = await checkboxGroupDefaultFocus.getInspectorInfo()
    assertTrue(JSON.parse(groupDefaultFocus1).$attrs.groupDefaultFocus)

    await button.tap()
    let groupDefaultFocus2: string = await checkboxGroupDefaultFocus.getInspectorInfo()
    assertFalse(JSON.parse(groupDefaultFocus2).$attrs.groupDefaultFocus)
  }, 0)
}