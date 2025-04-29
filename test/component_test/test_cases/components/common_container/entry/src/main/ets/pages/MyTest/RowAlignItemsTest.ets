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

export default async function rowAlignItemsTest() {
  /*
   * Row组件 AlignItems属性
   * 找到id为rowAlignItems1，rowAlignItems2的Row组件
   * 找到画面文本为RowAlignItems的Button组件
   * 获取row1的AlignItems属性与期待值VerticalAlign.Top比对
   * 获取row2的AlignItems属性与期待值VerticalAlign.Center比对
   * 点击button，变更row2的AlignItems属性值为VerticalAlign.Bottom
   * 获取row2的AlignItems属性与期待值VerticalAlign.Bottom比对
   */
  defineTest('rowAlignItemsTest', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('rowAlignItemsTestDemo running')
    let driver: Tester = Tester.create()
    let rowAlignItems1: Component = await driver.findComponent(Matcher.create().id('rowAlignItems1').enabled(true))
    let rowAlignItems2: Component = await driver.findComponent(Matcher.create().id('rowAlignItems2').enabled(true))
    let button: Component = await driver.findComponent((Matcher.create().text('RowAlignItems').enabled(true)))

    let alignItems1: string = await rowAlignItems1.getInspectorInfo()
    assertEqual(JSON.parse(alignItems1).$attrs.alignItems, 'VerticalAlign.Top')

    let alignItems2: string = await rowAlignItems2.getInspectorInfo()
    assertEqual(JSON.parse(alignItems2).$attrs.alignItems, 'VerticalAlign.Center')
    await button.tap()
    let alignItems3: string = await rowAlignItems2.getInspectorInfo()
    assertEqual(JSON.parse(alignItems3).$attrs.alignItems, 'VerticalAlign.Bottom')
  }, 0)
}