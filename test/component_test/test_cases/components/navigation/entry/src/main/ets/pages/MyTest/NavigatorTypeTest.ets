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

export default async function navigatorTypeTest() {
  /*
* Navigator组件 Type属性
* 找到画面id为NavigatorType1,NavigatorType2的Navigator组件
* 找到画面文本为NavigatorType的button组件
* 获取navigator1的Type属性与期待值NavigationType.Push比对
* 获取navigator2的Type属性与期待值NavigationType.Back比对
* 点击button，变更navigator的Type属性值为NavigationType.Replace
* 获取navigator的Type属性与期待值NavigationType.Replace比对
*/
  defineTest('navigatorTypeTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("navigatorTypeTestDemo running")
    let driver: Tester = Tester.create()
    let navigator1: Component = await driver.findComponent(Matcher.create().id('NavigatorType1').enabled(true))
    let navigator2: Component = await driver.findComponent(Matcher.create().id('NavigatorType2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('NavigatorType').enabled(true))

    let type1: string = await navigator1.getInspectorInfo()
    assertEqual(JSON.parse(type1).$attrs.type, 'NavigationType.Push')
    let type2: string = await navigator2.getInspectorInfo()
    assertEqual(JSON.parse(type2).$attrs.type, 'NavigationType.Replace')
    await button.tap()
    let type3: string = await navigator2.getInspectorInfo()
    assertEqual(JSON.parse(type3).$attrs.type, 'NavigationType.Back')
  }, 0)
}