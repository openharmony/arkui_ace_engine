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
import { assertEqual, Component, defineTest, Matcher, TestCaseLevel, Tester } from '@ohos.arkui.componentTest';

export default async function textTextCaseTest() {
  /*
* Text组件 TextCase属性
* 找到画面id为textTextCase1,textTextCase2的Text组件
* 找到画面文本为TextTextCase的Button组件
* 获取text1的TextCase属性与期待值TextCase.LowerCase比对
* 获取text2的TextCase属性与期待值TextCase.Normal比对
* 点击button，变更text2的TextCase属性值为TextCase.UpperCase
* 获取text2的TextCase属性与期待值TextCase.UpperCase比对
*/
  defineTest('textTextCaseTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("textTextCaseTestDemo running")
    let driver: Tester = Tester.create()
    let text1: Component = await driver.findComponent(Matcher.create().id('textTextCase1').enabled(true))
    let text2: Component = await driver.findComponent(Matcher.create().id('textTextCase2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('TextTextCase').enabled(true))

    let textCase1: string = await text1.getInspectorInfo()
    assertEqual(JSON.parse(textCase1).$attrs.textCase, 'TextCase.LowerCase')
    let textCase2: string = await text2.getInspectorInfo()
    assertEqual(JSON.parse(textCase2).$attrs.textCase, 'TextCase.Normal')

    await button.tap()
    let textCase3: string = await text2.getInspectorInfo()
    assertEqual(JSON.parse(textCase3).$attrs.textCase, 'TextCase.UpperCase')
  }, 0)
}