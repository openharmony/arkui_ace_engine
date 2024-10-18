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

export default async function requestFocusTest() {
  /*
  * 使用 Button组件 RequestFocus属性
  * 找到画面id为buttonRequestFocus1的Button组件
  * 找到画面文本为RequestFocus的Button组件
  * 获取buttonRequestFocus1的RequestFocus属性与期待值false比对
  * 点击button，变更buttonRequestFocus1的RequestFocus属性值为true
  * 获取buttonRequestFocus1的RequestFocus属性与期待值true比对
  */
  defineTest('requestFocusTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('requestFocusTestDemo running')
    let driver: Tester = Tester.create()
    let buttonRequestFocus1: Component =
      await driver.findComponent(Matcher.create().id('buttonRequestFocus1').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ButtonRequestFocus').enabled(true))
    let requestFocus1: string = await buttonRequestFocus1.getInspectorInfo()
    assertFalse(JSON.parse(requestFocus1).$attrs.requestFocus == undefined)
    assertFalse(JSON.parse(requestFocus1).$attrs.requestFocus)
    await button.tap()
    let requestFocus2: string = await buttonRequestFocus1.getInspectorInfo()
    assertTrue(JSON.parse(requestFocus2).$attrs.requestFocus)
  }, 0)
}