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

export default async function dividerLineCapTest() {
  /*
   * Divider组件 LineCap属性
   * 找到画面id为dividerLineCap1,dividerLineCap2的Divider组件
   * 找到画面文本为DividerLineCap的Button组件
   * 获取dividerLineCap1的LineCap属性与期待值BUTT比对
   * 获取dividerLineCap2的LineCap属性与期待值ROUND比对
   * 点击button，变更dividerLineCap2的LineCap属性值为LineCapStyle.Square
   * 获取dividerLineCap2的LineCap属性与期待值SQUARE比对
   */
  defineTest('dividerLineCapTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('dividerLineCapTestDemo running')
    let driver: Tester = Tester.create()
    let dividerLineCap1: Component = await driver.findComponent(Matcher.create().id('dividerLineCap1').enabled(true))
    let dividerLineCap2: Component = await driver.findComponent(Matcher.create().id('dividerLineCap2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('DividerLineCap').enabled(true))

    let lineCap1: string = await dividerLineCap1.getInspectorInfo()
    assertEqual(JSON.parse(lineCap1).$attrs.lineCap, 'BUTT')

    let lineCap2: string = await dividerLineCap2.getInspectorInfo()
    assertEqual(JSON.parse(lineCap2).$attrs.lineCap, 'ROUND')

    await button.tap()
    let lineCap3: string = await dividerLineCap2.getInspectorInfo()
    assertEqual(JSON.parse(lineCap3).$attrs.lineCap, 'SQUARE')
  }, 0)
}