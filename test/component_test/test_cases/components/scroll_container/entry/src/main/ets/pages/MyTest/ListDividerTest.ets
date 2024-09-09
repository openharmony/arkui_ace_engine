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

export default async function listDividerTest() {
  /*
   * List组件 Divider属性
   * 找到画面id为listDivider1,listDivider2的List组件
   * 找到画面文本为ListDivider1,ListDivider2的Button组件
   * 获取list1的Divider属性与期待值{strokeWidth:10.00vp,color:'#FFBBBBBB',startMargin:10.00vp,endMargin:10.00vp}比对
   * 获取list2的Divider属性与期待值{strokeWidth:$r('app.float.ListDivider_float'),color:$r('app.color.ListDivider_One_color'),
   * startMargin:$r('app.float.ListDivider_float'),endMargin:$r('app.float.ListDivider_float')}比对
   * 点击button1，变更list1的Divider属性值为{strokeWidth:'20.00px',color:'#FFFF64FF',startMargin:'20.00px',endMargin:'20.00px'}
   * 获取list1的Divider属性与期待值{strokeWidth:'20.00px',color:'#FFFF64FF',startMargin:'20.00px',endMargin:'20.00px'}比对
   * 点击button2，变更list1的Divider属性值为Color.Gray
   * 获取list1的Divider属性与期待值Color.Gray比对
   */
  defineTest('listDividerTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('listDividerTestDemo running')
    let driver: Tester = Tester.create()
    let list1: Component = await driver.findComponent(Matcher.create().id('listDivider1').enabled(true))
    let list2: Component = await driver.findComponent(Matcher.create().id('listDivider2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ListDivider1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('ListDivider2').enabled(true))

    let divider1: string = await list1.getInspectorInfo()
    assertEqual(JSON.parse(divider1).$attrs.divider.strokeWidth, '10.00vp')
    assertEqual(JSON.parse(divider1).$attrs.divider.color, '#FFBBBBBB')
    assertEqual(JSON.parse(divider1).$attrs.divider.startMargin, '10.00vp')
    assertEqual(JSON.parse(divider1).$attrs.divider.endMargin, '10.00vp')
    let divider2: string = await list2.getInspectorInfo()
    assertEqual(JSON.parse(divider2).$attrs.divider.strokeWidth, $r('app.float.ListDivider_float'))
    assertEqual(JSON.parse(divider2).$attrs.divider.color, $r('app.color.ListDivider_One_color'))
    assertEqual(JSON.parse(divider2).$attrs.divider.startMargin, $r('app.float.ListDivider_float'))
    assertEqual(JSON.parse(divider2).$attrs.divider.endMargin, $r('app.float.ListDivider_float'))
    await button1.tap()
    let divider3: string = await list1.getInspectorInfo()
    assertEqual(JSON.parse(divider3).$attrs.divider.strokeWidth, '20.00px')
    assertEqual(JSON.parse(divider3).$attrs.divider.color, '#FFFF64FF')
    assertEqual(JSON.parse(divider3).$attrs.divider.startMargin, '20.00px')
    assertEqual(JSON.parse(divider3).$attrs.divider.endMargin, '20.00px')
    await button2.tap()
    let divider4: string = await list2.getInspectorInfo()
    assertEqual(JSON.parse(divider4)
      .$attrs
      .divider
      .color
      .toLowerCase(), Color.Gray)
  }, 0)
}