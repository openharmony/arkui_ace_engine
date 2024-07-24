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

export default async function waterFlowFrictionTest() {
  /*
* WaterFlow组件  friction属性
* 找到画面id为waterFlowFriction1,waterFlowFriction2的waterFlow组件
* 找到画面文本为WaterFlowFriction的button组件
* 获取waterFlow1的friction属性与期待值0.7比对
* 获取waterFlow2的friction属性与期待值2比对
* 点击button，变更waterFlow1的friction属性值为$r('app.string.length')
* 获取waterFlow1的friction属性与期待值$$r('app.string.length')比对
*/
  defineTest('waterFlowFrictionTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("waterFlowFrictionTestDemo running")
    let driver: Tester = Tester.create()
    let waterFlow1: Component = await driver.findComponent(Matcher.create().id('waterFlowFriction1').enabled(true))
    let waterFlow2: Component = await driver.findComponent(Matcher.create().id('waterFlowFriction2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('WaterFlowFriction').enabled(true))

    let friction1: string = await waterFlow2.getInspectorInfo()
    assertEqual(JSON.parse(friction1).$attrs.friction, 0.7)
    let friction2: string = await waterFlow1.getInspectorInfo()
    assertEqual(JSON.parse(friction2).$attrs.friction, 2)
    await button.tap()
    let friction3: string = await waterFlow1.getInspectorInfo()
    assertEqual(JSON.parse(friction3).$attrs.friction, $r('app.string.length'))

  }, 0)
}