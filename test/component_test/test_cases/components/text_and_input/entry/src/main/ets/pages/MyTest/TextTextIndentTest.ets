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

export default async function textTextIndentTest() {
  /*
* Text组件 TextIndent属性
* 找到画面id为textTextIndent1,textTextIndent2的Text组件
* 找到画面文本为TextTextIndent的Button组件
* 获取text1的TextIndent属性与期待值$r('app.string.text')比对
* 获取text2的TextIndent属性与期待值100比对
* 点击button，变更text2的TextIndent属性值为'200px'
* 获取text2的TextIndent属性与期待值'200px'比对
*/
  defineTest('textTextIndentTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("textTextIndentTestDemo running")
    let driver: Tester = Tester.create()
    let text1: Component = await driver.findComponent(Matcher.create().id('textTextIndent1').enabled(true))
    let text2: Component = await driver.findComponent(Matcher.create().id('textTextIndent2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('TextTextIndent').enabled(true))

    let textIndent1: string = await text1.getInspectorInfo()
    assertEqual(JSON.parse(textIndent1).$attrs.textIndent, $r('app.string.fp_text'))
    let textIndent2: string = await text2.getInspectorInfo()
    assertEqual(JSON.parse(textIndent2).$attrs.textIndent, '100')

    await button.tap()
    let textIndent3: string = await text2.getInspectorInfo()
    assertEqual(JSON.parse(textIndent3).$attrs.textIndent, '200.00px')
  }, 0)
}