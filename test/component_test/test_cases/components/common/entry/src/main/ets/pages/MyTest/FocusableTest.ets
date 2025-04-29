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

export default async function focusableTest() {
  /*
  * 使用 Button组件 Focusable属性
  * 找到画面id为 buttonFocusable1 的Button组件
  * 找到画面文本为 ButtonFocusable 的Button组件
  * 获取buttonFocusable1的Focusable属性与期待值false比对
  * 点击button，变更buttonFocusable1的Focusable属性值为true
  * 获取buttonFocusable1的Focusable属性与期待值true比对
  */
  defineTest('focusableTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('focusableTestDemo running')
    let driver: Tester = Tester.create()
    let buttonFocusable1: Component = await driver.findComponent(Matcher.create().id('buttonFocusable1').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ButtonFocusable').enabled(true))
    let focusable1: string = await buttonFocusable1.getInspectorInfo()
    assertFalse(JSON.parse(focusable1).$attrs.focusable)

    await button.tap()
    let focusable2: string = await buttonFocusable1.getInspectorInfo()
    assertTrue(JSON.parse(focusable2).$attrs.focusable)
  }, 0)
}