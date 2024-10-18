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

export default async function columnSplitDividerTest() {
  /*
   * ColumnSplit组件 Divider属性
   * 找到id为columnSplitDivider1，columnSplitDivider2，columnSplitDivider3，columnSplitDivider4，columnSplitDivider5，columnSplitDivider6的Column组件
   * 找到画面文本为ColumnAlignItems的Button组件
   * 获取columnSplit1的Divider属性与期待值null比对
   * 获取columnSplit2的Divider属性与期待值{startMargin: $r('app.string.pixel_size'), endMargin: $r('app.string.pixel_size')}比对
   * 获取columnSplit3的Divider属性与期待值{startMargin: '100000%', endMargin: '100000%'}比对
   * 获取columnSplit4的Divider属性与期待值{startMargin: '10px', endMargin: '10px'}比对
   * 获取columnSplit5的Divider属性与期待值{startMargin: '10vp', endMargin: '10vp'}比对
   * 获取columnSplit6的Divider属性与期待值{startMargin: '10fp', endMargin: '10fp'}比对
   * 点击button，变更column6的Divider属性值为{startMargin: '10lpx', endMargin: '10lpx'}
   * 获取column6的Divider属性与期待值{startMargin: '10lpx', endMargin: '10lpx'}比对
   */

  defineTest('columnSplitDividerTest', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('columnSplitDividerTestDemo running')
    let driver: Tester = Tester.create()
    let columnSplitDivider1: Component = await driver.findComponent(Matcher.create()
      .id('columnSplitDivider1')
      .enabled(true))
    let columnSplitDivider2: Component = await driver.findComponent(Matcher.create()
      .id('columnSplitDivider2')
      .enabled(true))
    let columnSplitDivider3: Component = await driver.findComponent(Matcher.create()
      .id('columnSplitDivider3')
      .enabled(true))
    let columnSplitDivider4: Component = await driver.findComponent(Matcher.create()
      .id('columnSplitDivider4')
      .enabled(true))
    let columnSplitDivider5: Component = await driver.findComponent(Matcher.create()
      .id('columnSplitDivider5')
      .enabled(true))
    let columnSplitDivider6: Component = await driver.findComponent(Matcher.create()
      .id('columnSplitDivider6')
      .enabled(true))
    let button: Component = await driver.findComponent((Matcher.create().text('ColumnSplitDivider').enabled(true)))

    let divider1: string = await columnSplitDivider1.getInspectorInfo()
    assertEqual(JSON.parse(divider1).$attrs.divider.startMargin, undefined)
    assertEqual(JSON.parse(divider1).$attrs.divider.endMargin, undefined)

    let divider2: string = await columnSplitDivider2.getInspectorInfo()
    assertEqual(JSON.parse(divider2).$attrs.divider.startMargin, $r('app.string.pixel_float_size'))
    assertEqual(JSON.parse(divider2).$attrs.divider.endMargin, $r('app.string.pixel_float_size'))

    let divider3: string = await columnSplitDivider3.getInspectorInfo()
    assertEqual(JSON.parse(divider3).$attrs.divider.startMargin, '100000.00%')
    assertEqual(JSON.parse(divider3).$attrs.divider.endMargin, '100000.00%')

    let divider4: string = await columnSplitDivider4.getInspectorInfo()
    assertEqual(JSON.parse(divider4).$attrs.divider.startMargin, '10.00px')
    assertEqual(JSON.parse(divider4).$attrs.divider.endMargin, '10.00px')

    let divider5: string = await columnSplitDivider5.getInspectorInfo()
    assertEqual(JSON.parse(divider5).$attrs.divider.startMargin, '10.00vp')
    assertEqual(JSON.parse(divider5).$attrs.divider.endMargin, '10.00vp')

    let divider6: string = await columnSplitDivider6.getInspectorInfo()
    assertEqual(JSON.parse(divider6).$attrs.divider.startMargin, '10.00fp')
    assertEqual(JSON.parse(divider6).$attrs.divider.endMargin, '10.00fp')
    await button.tap()
    let divider7: string = await columnSplitDivider6.getInspectorInfo()
    assertEqual(JSON.parse(divider7).$attrs.divider.startMargin, '10.00lpx')
    assertEqual(JSON.parse(divider7).$attrs.divider.endMargin, '10.00lpx')
  }, 0)
}