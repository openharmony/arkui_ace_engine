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

export default async function waterFlowRowsTemplateTest() {
  /*
* WaterFlow组件 rowsTemplate属性
* 找到画面id为waterFlowRowsTemplate的waterFlow组件
* 获取waterFlow的rowsTemplate属性与期待值'1fr 1fr 2fr'比对
*/
  defineTest('waterFlowRowsTemplateTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("waterFlowRowsTemplateTestDemo running")
    let driver: Tester = Tester.create()
    let waterFlow: Component = await driver.findComponent(Matcher.create().id('waterFlowRowsTemplate').enabled(true))

    let rowsTemplate: string = await waterFlow.getInspectorInfo()
    assertEqual(JSON.parse(rowsTemplate).$attrs.rowsTemplate, '1fr 1fr 2fr')
  }, 0)
}