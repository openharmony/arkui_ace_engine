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

export default async function listItemGroupDividerTest() {
  /*
* ListItemGroup组件 Divider属性
* 找到画面id为listItemGroupDivider1, listItemGroupDivider2, listItemGroupDivider3的listItemGroup组件
* 找到画面文本为ListItemGroupDivider1, ListItemGroupDivider2的button组件
* 获取listItemGroup1的divider属性的strokeWidth参数与期待值5.00vp比对
* 获取listItemGroup1的divider属性的color参数与期待值Color.Blue比对
* 获取listItemGroup1的divider属性的startMargin参数与期待值'100.00px'比对
* 获取listItemGroup1的divider属性的endMargin参数与期待值20.00vp比对
* 点击button1，变更listItemGroup1的divider属性的参数各变换为strokeWidth：'50.00px'， color：#FFFF00FF
* 获取listItemGroup1的divider属性的strokeWidth参数与期待值'50.00px'比对
* 获取listItemGroup1的divider属性的color参数与期待值#FFFF00FF比对
* 获取listItemGroup2的divider属性的strokeWidth参数与期待值$r('app.string.listItemGroup_strokeWidth')比对
* 获取listItemGroup2的divider属性的color参数与期待值'#FFFFF000'比对
* 获取listItemGroup2的divider属性的startMargin参数与期待值$r('app.string.listItemGroup_startMargin')比对
* 获取listItemGroup2的divider属性的endMargin参数与期待值'50.00px'比对
* 点击button2，变更listItemGroup2的divider属性的参数各变换为color：$r('app.color.listItemGroup_color')，startMargin：$r('app.integer.listItemGroup_endMargin')， endMargin：'50.00vp'
* 获取listItemGroup2的divider属性的color参数与期待值$r('app.color.listItemGroup_color')比对
* 获取listItemGroup2的divider属性的startMargin参数与期待值50比对
* 获取listItemGroup2的divider属性的endMargin参数与期待值$r('app.string.listItemGroup_endMargin')比对
* 获取listItemGroup3的divider属性的strokeWidth参数与期待值'0.00vp'比对
* 获取listItemGroup3的divider属性的color参数与期待值'#00000000'比对
* 获取listItemGroup3的divider属性的startMargin参数与期待值'0.00vp'比对
* 获取listItemGroup3的divider属性的endMargin参数与期待值'0.00vp'比对
*/
  defineTest('listItemGroupDividerTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('listItemGroupDividerTestDemo running')
    let driver: Tester = Tester.create()
    let listItemGroup1: Component =
      await driver.findComponent(Matcher.create().id('listItemGroupDivider1').enabled(true))
    let listItemGroup2: Component =
      await driver.findComponent(Matcher.create().id('listItemGroupDivider2').enabled(true))
    let listItemGroup3: Component =
      await driver.findComponent(Matcher.create().id('listItemGroupDivider3').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ListItemGroup1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('ListItemGroup2').enabled(true))

    let divider1: string = await listItemGroup1.getInspectorInfo()
    assertEqual(JSON.parse(divider1).$attrs.divider.strokeWidth, '5.00vp')
    assertEqual(JSON.parse(divider1)
      .$attrs
      .divider
      .color
      .toLowerCase(), Color.Blue)
    assertEqual(JSON.parse(divider1).$attrs.divider.startMargin, '100.00px')
    assertEqual(JSON.parse(divider1).$attrs.divider.endMargin, '20.00vp')
    await button1.tap()
    let divider2: string = await listItemGroup1.getInspectorInfo()
    assertEqual(JSON.parse(divider2).$attrs.divider.strokeWidth, '50.00px')
    assertEqual(JSON.parse(divider2).$attrs.divider.color, '#FFFF00FF')
    assertEqual(JSON.parse(divider2).$attrs.divider.startMargin, '100.00px')
    assertEqual(JSON.parse(divider2).$attrs.divider.endMargin, '20.00vp')
    let divider3: string = await listItemGroup2.getInspectorInfo()
    assertEqual(JSON.parse(divider3).$attrs.divider.strokeWidth, $r('app.string.listItemGroup_strokeWidth'))
    assertEqual(JSON.parse(divider3).$attrs.divider.color, '#FFFFF000')
    assertEqual(JSON.parse(divider3).$attrs.divider.startMargin, $r('app.string.listItemGroup_startMargin'))
    assertEqual(JSON.parse(divider3).$attrs.divider.endMargin, '50.00px')
    await button2.tap()
    let divider4: string = await listItemGroup2.getInspectorInfo()
    assertEqual(JSON.parse(divider4).$attrs.divider.strokeWidth, $r('app.string.listItemGroup_strokeWidth'))
    assertEqual(JSON.parse(divider4).$attrs.divider.color, $r('app.color.listItemGroup_color'))
    assertEqual(JSON.parse(divider4).$attrs.divider.startMargin, $r('app.string.listItemGroup_endMargin'))
    assertEqual(JSON.parse(divider4).$attrs.divider.endMargin, '50.00vp')
    let divider5: string = await listItemGroup3.getInspectorInfo()
    assertEqual(JSON.parse(divider5).$attrs.divider.strokeWidth, '0.00vp')
    assertEqual(JSON.parse(divider5).$attrs.divider.color, '#00000000')
    assertEqual(JSON.parse(divider5).$attrs.divider.startMargin, '0.00vp')
    assertEqual(JSON.parse(divider5).$attrs.divider.endMargin, '0.00vp')
  }, 0)
}