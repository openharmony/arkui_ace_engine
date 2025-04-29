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

export default async function textLetterSpacingTest() {
  /*
* Text组件 LetterSpacing属性
* 找到画面id为textLetterSpacing1的Text组件
* 找到画面文本为TextLetterSpacing的Button组件
* 获取text的LetterSpacing属性与期待值10比对
* 点击button，变更text的LetterSpacing属性值为'20px'
* 获取text的LetterSpacing属性与期待值'20px'比对
*/
  defineTest('textLetterSpacingTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("textLetterSpacingTestDemo running")
    let driver: Tester = Tester.create()
    let text: Component = await driver.findComponent(Matcher.create().id('textLetterSpacing1').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('TextLetterSpacing').enabled(true))

    let letterSpacing1: string = await text.getInspectorInfo()
    assertEqual(JSON.parse(letterSpacing1).$attrs.letterSpacing, '10.00fp')

    await button.tap()
    let letterSpacing2: string = await text.getInspectorInfo()
    assertEqual(JSON.parse(letterSpacing2).$attrs.letterSpacing, '20.00px')
  }, 0)
}