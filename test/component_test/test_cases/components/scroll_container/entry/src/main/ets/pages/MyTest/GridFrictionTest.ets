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

export default async function gridFrictionTest() {
  /*
  * Grid组件 Friction属性
  * 找到画面id为gridFriction1，gridFriction2的Grid组件
  * 找到画面文本为GridFriction的Button组件
  * 获取gridFriction1的Friction属性与期待值0.7比对
  * 获取gridFriction2的Friction属性与期待值0.6比对
  * 点击button，变更gridFriction2的Friction属性值为$r('app.float.offset_max')
  * 获取gridFriction2的Friction属性与期待值$r('app.float.offset_max')比对
  */
  defineTest('gridFrictionTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('gridFrictionTestDemo running')
    let driver: Tester = Tester.create()
    let gridFriction1: Component = await driver.findComponent(Matcher.create().id('gridFriction1').enabled(true))
    let gridFriction2: Component = await driver.findComponent(Matcher.create().id('gridFriction2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('GridFriction').enabled(true))

    let friction1: string = await gridFriction1.getInspectorInfo()
    assertEqual(JSON.parse(friction1).$attrs.friction, 0.7)
    let friction2: string = await gridFriction2.getInspectorInfo()
    assertEqual(JSON.parse(friction2).$attrs.friction, 0.6)
    await button.tap()
    let friction3: string = await gridFriction2.getInspectorInfo()
    assertEqual(JSON.parse(friction3).$attrs.friction, $r('app.float.offset_max'))
  }, 0)
}