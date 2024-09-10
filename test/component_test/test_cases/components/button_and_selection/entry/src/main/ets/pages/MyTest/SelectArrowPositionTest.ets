/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 // * You may obtain a copy of the License at
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

export default async function selectArrowPositionTest() {
  /*
  * Select组件 ArrowPosition属性
  * 找到画面id为selectArrowPosition的Select组件
  * 找到画面文本为SelectArrowPosition的Button组件
  * 获取selectArrowPosition的ArrowPosition属性与期待值'ArrowPosition.END'比对
  * 点击button，变更selectArrowPosition的ArrowPosition属性值为'ArrowPosition.START'
  * 获取selectArrowPosition的ArrowPosition属性与期待值'ArrowPosition.START'比对
  */
  defineTest('selectArrowPositionTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('selectArrowPositionTestDemo running')
    let driver: Tester = Tester.create()
    let selectArrowPosition: Component =
      await driver.findComponent(Matcher.create().id('selectArrowPosition').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('SelectArrowPosition').enabled(true))

    let arrowPosition1: string = await selectArrowPosition.getInspectorInfo()
    assertEqual(JSON.parse(arrowPosition1).$attrs.arrowPosition, 'ArrowPosition.END')

    await button.tap()
    let arrowPosition2: string = await selectArrowPosition.getInspectorInfo()
    assertEqual(JSON.parse(arrowPosition2).$attrs.arrowPosition, 'ArrowPosition.START')
  }, 0)
}