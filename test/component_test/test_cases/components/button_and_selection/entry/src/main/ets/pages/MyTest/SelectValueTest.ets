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

export default async function selectValueTest() {
  /*
  * Select组件 Value 属性
  * 找到画面id为selectValue的Select组件
  * 找到画面文本为SelectValue的Button组件
  * 获取selectValue的Value属性与期待值'2'比对
  * 点击button，变更selectValue的Value属性值为$r('app.string.select_value')
  * 获取selectValue的Value属性与期待值$r('app.string.select_value')比对
  */
  defineTest('selectValueTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('selectValueTestDemo running')
    let driver: Tester = Tester.create()
    let selectValue: Component = await driver.findComponent(Matcher.create().id('selectValue').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('SelectValue').enabled(true))

    let value1: string = await selectValue.getInspectorInfo()
    assertEqual(JSON.parse(value1).$attrs.value, '2')

    await button.tap()
    let value2: string = await selectValue.getInspectorInfo()
    assertEqual(JSON.parse(value2).$attrs.value, $r('app.string.select_value'))
  }, 0)
}