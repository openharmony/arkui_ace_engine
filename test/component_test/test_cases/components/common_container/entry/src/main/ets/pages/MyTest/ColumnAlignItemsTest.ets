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

export default async function columnAlignItemsTest() {
  /*
   * Column组件 AlignItems属性
   * 找到id为columnAlignItems1，columnAlignItems2的Column组件
   * 找到画面文本为ColumnAlignItems的Button组件
   * 获取column1的AlignItems属性与期待值HorizontalAlign.Start比对
   * 获取column2的AlignItems属性与期待值HorizontalAlign.Center比对
   * 点击button，变更column2的AlignItems属性值为HorizontalAlign.End
   * 获取column2的AlignItems属性与期待值HorizontalAlign.End比对
   */
  defineTest('columnAlignItemsTest', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('columnAlignItemsTestDemo running')
    let driver: Tester = Tester.create()
    let columnAlignItems1: Component = await driver.findComponent(Matcher.create()
      .id('columnAlignItems1')
      .enabled(true))
    let columnAlignItems2: Component = await driver.findComponent(Matcher.create()
      .id('columnAlignItems2')
      .enabled(true))
    let button: Component = await driver.findComponent((Matcher.create().text('ColumnAlignItems').enabled(true)))

    let alignItems1: string = await columnAlignItems1.getInspectorInfo()
    assertEqual(JSON.parse(alignItems1).$attrs.alignItems, 'HorizontalAlign.Start')

    let alignItems2: string = await columnAlignItems2.getInspectorInfo()
    assertEqual(JSON.parse(alignItems2).$attrs.alignItems, 'HorizontalAlign.Center')
    await button.tap()
    let alignItems3: string = await columnAlignItems2.getInspectorInfo()
    assertEqual(JSON.parse(alignItems3).$attrs.alignItems, 'HorizontalAlign.End')
  }, 0)
}