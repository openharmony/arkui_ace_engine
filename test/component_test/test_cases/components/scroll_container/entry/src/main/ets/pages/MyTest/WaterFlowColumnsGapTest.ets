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

export default async function waterFlowColumnsGapTest() {
  /*
* WaterFlow组件 columnsGap属性
* 找到画面id为waterFlowColumnsGap1,waterFlowColumnsGap2的waterFlow组件
* 找到画面文本为WaterFlowColumnsGap的button组件
* 获取waterFlow1的columnsGap属性与期待值$r('app.string.length')比对
* 获取waterFlow2的columnsGap属性与期待值'10.00vp'比对
* 点击button，变更waterFlow2的columnsGap属性值为'80.00px'
* 获取waterFlow2的columnsGap属性与期待值'80.00px'比对
*/
  defineTest('waterFlowColumnsGapTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("waterFlowColumnsGapTestDemo running")
    let driver: Tester = Tester.create()
    let waterFlow1: Component = await driver.findComponent(Matcher.create().id('waterFlowColumnsGap1').enabled(true))
    let waterFlow2: Component = await driver.findComponent(Matcher.create().id('waterFlowColumnsGap2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('WaterFlowColumnsGap').enabled(true))

    let columnsGap1: string = await waterFlow1.getInspectorInfo()
    assertEqual(JSON.parse(columnsGap1).$attrs.columnsGap, $r('app.string.length'))
    let columnsGap2: string = await waterFlow2.getInspectorInfo()
    assertEqual(JSON.parse(columnsGap2).$attrs.columnsGap, '10.00vp')
    await button.tap()
    let columnsGap3: string = await waterFlow2.getInspectorInfo()
    assertEqual(JSON.parse(columnsGap3).$attrs.columnsGap, '80.00px')
  }, 0)
}