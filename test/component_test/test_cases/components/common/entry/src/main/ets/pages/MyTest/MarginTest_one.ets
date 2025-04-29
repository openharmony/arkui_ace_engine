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

export default async function marginTest_one() {
  /*
   * Text组件 Margin通用属性
   * 找到画面id为textMargin的组件
   * 找到画面text为ButtonTextMargin的button组件
   * 获取textMargin的Margin属性与期待值 '10.00px' 比较
   * 点击button变更textMargin的属性值与期待值 '10.00vp' 比较
   * 点击button变更textMargin的属性值与期待值 $r('app.string.common_breadth') 比较
   */
  defineTest('marginTest_oneDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('marginTest_oneDemo running')
    let driver: Tester = Tester.create()
    let textMargin: Component = await driver.findComponent(Matcher.create().id('textMargin1').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ButtonTextMargin').enabled(true))
    let information1: string = await textMargin.getInspectorInfo()
    assertEqual(JSON.parse(information1).$attrs.margin, '10.00px')

    await button.tap()
    let information2: string = await textMargin.getInspectorInfo()
    assertEqual(JSON.parse(information2).$attrs.margin, '10.00vp')

    await button.tap()
    let information3: string = await textMargin.getInspectorInfo()
    assertEqual(JSON.parse(information3).$attrs.margin, $r('app.string.common_breadth'))
  }, 0)
}