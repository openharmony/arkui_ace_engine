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

export default async function selectSelectedTest() {
  /*
   * Select组件 Selected属性
   * 找到画面id为selectSelected1，selectSelected2，selectSelected3的Select组件
   * 找到画面文本为SelectSelected的Button组件
   * 获取selectSelected1的Selected属性与期待值'0'比对
   * 获取selectSelected2的Selected属性与期待值'0'比对
   * 获取selectSelected3的Selected属性与期待值'1'比对
   * 点击button，变更selectSelected3的Selected属性值为$r('app.string.selected_index')
   * 获取selectSelected3的Selected属性与期待值$r('app.string.selected_index')比对
   */
  defineTest('selectSelectedTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('selectSelectedTestDemo running')
    let driver: Tester = Tester.create()
    let selectSelected1: Component = await driver.findComponent(Matcher.create().id('selectSelected1').enabled(true))
    let selectSelected2: Component = await driver.findComponent(Matcher.create().id('selectSelected2').enabled(true))
    let selectSelected3: Component = await driver.findComponent(Matcher.create().id('selectSelected3').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('SelectSelected').enabled(true))

    let selected1: string = await selectSelected1.getInspectorInfo()
    assertEqual(JSON.parse(selected1).$attrs.selected, '0')

    let selected2: string = await selectSelected2.getInspectorInfo()
    assertEqual(JSON.parse(selected2).$attrs.selected, '0')

    let selected3: string = await selectSelected3.getInspectorInfo()
    assertEqual(JSON.parse(selected3).$attrs.selected, '1')

    await button.tap()
    let selected4: string = await selectSelected3.getInspectorInfo()
    assertEqual(JSON.parse(selected4).$attrs.selected, $r('app.string.selected_index'))
  }, 0)
}