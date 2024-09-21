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

export default async function listLanesTest() {
  /*
   * List组件 Lanes属性
   * 找到画面id为listLanes1,listLanes2,listLanes3的List组件
   * 找到画面文本为ListLanes1,ListLanes2,ListLanes3的Button组件
   * 获取list1的Lanes属性与期待值{20,gutter:'10.00px'}比对
   * 获取list2的Lanes属性与期待值{minLength:$r('app.float.ListLanes_float'),maxLength:$r('app.float.ListLanes_float'),gutter:'10.00fp'}比对
   * 获取list3的Lanes属性与期待值{minLength:$r('app.float.ListLanes_float'),maxLength:$r('app.float.ListLanes_float'),gutter:'10%'}比对
   * 点击button1，变更list1的Lanes属性值为{minLength:'5.00px',maxLength: '5.00px',gutter:'10.00vp'}
   * 获取list1的Lanes属性与期待值{minLength:'5.00px',maxLength: '5.00px',gutter:'10.00vp'}比对
   * 点击button2，变更list1的Lanes属性值为{minLength:5,maxLength:5,gutter:'10lpx'}
   * 获取list1的Lanes属性与期待值{minLength:5.00vp,maxLength:'5.00vp',gutter:'10.00vp'}比对
   * 点击button3，变更list1的Lanes属性值为 $r('app.float.ListLanes_float')
   * 获取list1的Lanes属性与期待值 $r('app.float.ListLanes_float')比对
   */
  defineTest('listLanesTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('listLanesTestDemo running')
    let driver: Tester = Tester.create()
    let list1: Component = await driver.findComponent(Matcher.create().id('listLanes1').enabled(true))
    let list2: Component = await driver.findComponent(Matcher.create().id('listLanes2').enabled(true))
    let list3: Component = await driver.findComponent(Matcher.create().id('listLanes3').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ListLanes1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('ListLanes2').enabled(true))
    let button3: Component = await driver.findComponent(Matcher.create().text('ListLanes3').enabled(true))

    let lanes1: string = await list1.getInspectorInfo()
    assertEqual(JSON.parse(lanes1).$attrs.lanes, '20')
    assertEqual(JSON.parse(lanes1).$attrs.laneGutter, '10.00px')
    let lanes2: string = await list2.getInspectorInfo()
    assertEqual(JSON.parse(lanes2).$attrs.laneMinLength, $r('app.float.ListLanes_float'))
    assertEqual(JSON.parse(lanes2).$attrs.laneMaxLength, $r('app.float.ListLanes_float'))
    assertEqual(JSON.parse(lanes2).$attrs.laneGutter, '10.00fp')
    let lanes3: string = await list3.getInspectorInfo()
    assertEqual(JSON.parse(lanes3).$attrs.laneMinLength, $r('app.float.ListLanes_float'))
    assertEqual(JSON.parse(lanes3).$attrs.laneMaxLength, $r('app.float.ListLanes_float'))
    assertEqual(JSON.parse(lanes3).$attrs.laneGutter, '10.00%')
    await button1.tap()
    let lanes4: string = await list1.getInspectorInfo()
    assertEqual(JSON.parse(lanes4).$attrs.laneMinLength, '5.00px')
    assertEqual(JSON.parse(lanes4).$attrs.laneMaxLength, '5.00px')
    assertEqual(JSON.parse(lanes4).$attrs.laneGutter, '10.00vp')
    await button2.tap()
    let lanes5: string = await list1.getInspectorInfo()
    assertEqual(JSON.parse(lanes5).$attrs.laneMinLength, '5.00px')
    assertEqual(JSON.parse(lanes5).$attrs.laneMaxLength, '5.00px')
    assertEqual(JSON.parse(lanes5).$attrs.laneGutter, '10.00vp')
    await button3.tap()
    let lanes6: string = await list3.getInspectorInfo()
    assertEqual(JSON.parse(lanes6).$attrs.laneGutter, $r('app.float.ListLanes_float'))
  }, 0)
}