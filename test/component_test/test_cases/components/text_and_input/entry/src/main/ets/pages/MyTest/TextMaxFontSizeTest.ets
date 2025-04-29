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

export default async function textMaxFontSizeTest() {
  /*
* Text组件 MaxFontSize属性
* 找到画面id为textMaxFontSize1,textMaxFontSize2的Text组件
* 找到画面文本为TextMaxFontSize的Button组件
* 获取text1的MaxFontSize属性与期待值$r('app.string.text')比对
* 获取text2的MaxFontSize属性与期待值30比对
* 点击button，变更text2的MaxFontSize属性值为'20px'
* 获取text2的MaxFontSize属性与期待值'20px'比对
*/
  defineTest('textMaxFontSizeTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("textMaxFontSizeTestDemo running")
    let driver: Tester = Tester.create()
    let text1: Component = await driver.findComponent(Matcher.create().id('textMaxFontSize1').enabled(true))
    let text2: Component = await driver.findComponent(Matcher.create().id('textMaxFontSize2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('TextMaxFontSize').enabled(true))

    let maxFontSize1: string = await text1.getInspectorInfo()
    assertEqual(JSON.parse(maxFontSize1).$attrs.maxFontSize, $r('app.string.fp_text'))
    let maxFontSize2: string = await text2.getInspectorInfo()
    assertEqual(JSON.parse(maxFontSize2).$attrs.maxFontSize, '30.00fp')

    await button.tap()
    let maxFontSize3: string = await text2.getInspectorInfo()
    assertEqual(JSON.parse(maxFontSize3).$attrs.maxFontSize, '20.00px')
  }, 0)
}