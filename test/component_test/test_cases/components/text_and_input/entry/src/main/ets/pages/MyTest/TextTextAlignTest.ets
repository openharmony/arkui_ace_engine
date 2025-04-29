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

export default async function textTextAlignTest() {
  /*
* Text组件 TextAlign属性
* 找到画面id为textTextAlign1,textTextAlign2的Text组件
* 找到画面文本为TextTextAlign1,TextTextAlign2的Button组件
* 获取text1的TextAlign属性与期待值TextAlign.Center比对
* 获取text2的TextAlign属性与期待值TextAlign.JUSTIFY比对
* 点击button1，变更text1的TextAlign属性值为TextAlign.Start
* 获取text1的TextAlign属性与期待值TextAlign.Start比对
* 点击button2，变更text1的TextAlign属性值为TextAlign.End
* 获取text1的TextAlign属性与期待值TextAlign.End比对
*/
  defineTest('textTextAlignTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("textTextAlignTestDemo running")
    let driver: Tester = Tester.create()
    let text1: Component = await driver.findComponent(Matcher.create().id('textTextAlign1').enabled(true))
    let text2: Component = await driver.findComponent(Matcher.create().id('textTextAlign2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('TextTextAlign1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('TextTextAlign2').enabled(true))

    let textAlign1: string = await text1.getInspectorInfo()
    assertEqual(JSON.parse(textAlign1).$attrs.textAlign, 'TextAlign.Center')
    let textAlign2: string = await text2.getInspectorInfo()
    assertEqual(JSON.parse(textAlign2).$attrs.textAlign, 'TextAlign.Justify')

    await button1.tap()
    let textAlign3: string = await text2.getInspectorInfo()
    assertEqual(JSON.parse(textAlign3).$attrs.textAlign, 'TextAlign.Start')
    await button2.tap()
    let textAlign4: string = await text2.getInspectorInfo()
    assertEqual(JSON.parse(textAlign4).$attrs.textAlign, 'TextAlign.End')
  }, 0)
}