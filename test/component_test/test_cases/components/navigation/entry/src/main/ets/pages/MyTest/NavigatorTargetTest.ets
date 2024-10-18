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

export default async function navigatorTargetTest() {
  /*
* Navigator组件 Target属性
* 找到画面id为navigatorTarget的Navigator组件
* 找到画面文本为NavigatorTarget的button组件
* 获取navigator的Target属性与期待值'pages/navigator/NavigatorActiveTypeDetail'比对
*/
  defineTest('navigatorTargetTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("navigatorTargetTestDemo running")
    let driver: Tester = Tester.create()
    let navigator: Component = await driver.findComponent(Matcher.create().id('navigatorTarget').enabled(true))

    let target: string = await navigator.getInspectorInfo()
    assertEqual(JSON.parse(target).$attrs.target, 'pages/navigator/NavigatorActiveTypeDetail')
  }, 0)
}