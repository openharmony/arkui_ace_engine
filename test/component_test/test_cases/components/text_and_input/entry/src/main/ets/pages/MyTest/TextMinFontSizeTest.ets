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

export default async function textMinFontSizeTest() {
  /*
* Text组件 MinFontSize属性
* 找到画面id为textMinFontSize1,textMinFontSize2的Text组件
* 找到画面文本为TextMinFontSize的Button组件
* 获取text1的MinFontSize属性与期待值$r('app.string.text')比对
* 获取text2的MinFontSize属性与期待值30比对
* 点击button，变更text2的MinFontSize属性值为'20px'
* 获取text2的MinFontSize属性与期待值'20px'比对
*/
  defineTest('textMinFontSizeTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("textMinFontSizeTestDemo running")
    let driver: Tester = Tester.create()
    let text1: Component = await driver.findComponent(Matcher.create().id('textMinFontSize1').enabled(true))
    let text2: Component = await driver.findComponent(Matcher.create().id('textMinFontSize2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('TextMinFontSize').enabled(true))

    let minFontSize1: string = await text1.getInspectorInfo()
    assertEqual(JSON.parse(minFontSize1).$attrs.minFontSize, $r('app.string.fp_text'))
    let minFontSize2: string = await text2.getInspectorInfo()
    assertEqual(JSON.parse(minFontSize2).$attrs.minFontSize, '10.00fp')

    await button.tap()
    let minFontSize3: string = await text2.getInspectorInfo()
    assertEqual(JSON.parse(minFontSize3).$attrs.minFontSize, '20.00px')
  }, 0)
}