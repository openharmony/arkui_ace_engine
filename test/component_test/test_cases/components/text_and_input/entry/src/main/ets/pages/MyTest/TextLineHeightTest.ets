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

export default async function textLineHeightTest() {
  /*
* Text组件 LineHeight属性
* 找到画面id为textLineHeight1的Text组件
* 找到画面文本为TextLineHeight1,TextLineHeight2的Button组件
* 获取text的LineHeight属性与期待值50比对
* 点击button1，变更text的LineHeight属性值为'50px'
* 获取text的LineHeight属性与期待值'50px'比对
* 点击button2，变更text的LineHeight属性值为$r('app.string.line_height')
* 获取text的LineHeight属性与期待值$r('app.string.line_height')比对
*/
  defineTest('textLineHeightTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("textLineHeightTestDemo running")
    let driver: Tester = Tester.create()
    let text: Component = await driver.findComponent(Matcher.create().id('textLineHeight1').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('TextLineHeight1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('TextLineHeight2').enabled(true))

    let lineHeight1: string = await text.getInspectorInfo()
    assertEqual(JSON.parse(lineHeight1).$attrs.lineHeight, '50.00fp')

    await button1.tap()
    let lineHeight2: string = await text.getInspectorInfo()
    assertEqual(JSON.parse(lineHeight2).$attrs.lineHeight, '50.00px')
    await button2.tap()
    let lineHeight3: string = await text.getInspectorInfo()
    assertEqual(JSON.parse(lineHeight3).$attrs.lineHeight, $r('app.string.fp_line_height'))
  }, 0)
}