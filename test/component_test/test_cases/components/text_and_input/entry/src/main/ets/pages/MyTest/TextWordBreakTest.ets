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

export default async function textWordBreakTest() {
  /*
* Text组件 WordBreak属性
* 找到画面id为textWordBreak1,textWordBreak2的Text组件
* 找到画面文本为TextWordBreak的Button组件
* 获取text1的WordBreak属性与期待值WordBreak.BREAK_ALL比对
* 获取text2的WordBreak属性与期待值WordBreak.NORMAL比对
* 点击button，变更text2的WordBreak属性值为WordBreak.BREAK_WORD
* 获取text2的WordBreak属性与期待值WordBreak.BREAK_WORD比对
*/
  defineTest('textWordBreakTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("textWordBreakTestDemo running")
    let driver: Tester = Tester.create()
    let text1: Component = await driver.findComponent(Matcher.create().id('textWordBreak1').enabled(true))
    let text2: Component = await driver.findComponent(Matcher.create().id('textWordBreak2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('TextWordBreak').enabled(true))

    let wordBreak1: string = await text1.getInspectorInfo()
    assertEqual(JSON.parse(wordBreak1).$attrs.wordBreak, 'break-all')
    let wordBreak2: string = await text2.getInspectorInfo()
    assertEqual(JSON.parse(wordBreak2).$attrs.wordBreak, 'normal')

    await button.tap()
    let wordBreak3: string = await text2.getInspectorInfo()
    assertEqual(JSON.parse(wordBreak3).$attrs.wordBreak, 'break-word')
  }, 0)
}