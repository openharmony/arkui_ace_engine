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

export default async function progressValueTest() {
  /*
* Progress组件 Value属性
* 找到画面id为progressValue1,progressValue2的Progress组件
* 获取progress1的Value属性与期待值80比对
* 获取progress2的Value属性与期待值0比对
*/
  defineTest('progressValueTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("progressValueTestDemo running")
    let driver: Tester = Tester.create()
    let progress1: Component = await driver.findComponent(Matcher.create().id('progressValue1').enabled(true))
    let progress2: Component = await driver.findComponent(Matcher.create().id('progressValue2').enabled(true))
    let value1: string = await progress1.getInspectorInfo()
    assertEqual(JSON.parse(value1).$attrs.value, '80.000000')
    let value2: string = await progress2.getInspectorInfo()
    assertEqual(JSON.parse(value2).$attrs.value, '0.000000')
  }, 0)
}