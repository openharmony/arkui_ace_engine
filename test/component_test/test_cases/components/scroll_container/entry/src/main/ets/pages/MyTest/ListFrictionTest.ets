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

export default async function listFrictionTest() {
  /*
   * List组件 Friction属性
   * 找到画面id为listFriction1,listFriction2的List组件
   * 找到画面文本为ListFriction1,ListFriction2的Button组件
   * 获取list1的Friction属性与期待值0.1比对
   * 获取list2的Friction属性与期待值0.7比对
   * 点击button，变更list1的Friction属性值为1
   * 获取list1的Friction属性与期待值1比对
   * 点击button，变更list1的Friction属性值为'app.float.ListFriction_float'
   * 获取list1的Friction属性与期待值'app.float.ListFriction_float'比对
   */
  defineTest('listFrictionTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('listFrictionTestDemo running')
    let driver: Tester = Tester.create()
    let list1: Component = await driver.findComponent(Matcher.create().id('listFriction1').enabled(true))
    let list2: Component = await driver.findComponent(Matcher.create().id('listFriction2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ListFriction1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('ListFriction2').enabled(true))

    let friction1: string = await list1.getInspectorInfo()
    assertEqual(JSON.parse(friction1).$attrs.friction, 0.1)
    let friction2: string = await list2.getInspectorInfo()
    assertEqual(JSON.parse(friction2).$attrs.friction, 0.7)
    await button1.tap()
    let friction3: string = await list1.getInspectorInfo()
    assertEqual(JSON.parse(friction3).$attrs.friction, 1)
    await button2.tap()
    let friction4: string = await list1.getInspectorInfo()
    assertEqual(JSON.parse(friction4).$attrs.friction, 'app.float.ListFriction_float')
  }, 0)
}