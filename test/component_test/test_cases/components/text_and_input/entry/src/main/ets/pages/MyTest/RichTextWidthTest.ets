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

/*
* RichText组件 Width属性
* 找到画面id为richTextWidth1,richTextWidth2的RichText组件
* 找到画面文本为RichTextWidth的Button组件
* 获取richText1的Width属性与期待值500.00vp比对
* 获取richText2的Width属性与期待值'100.00px'比对
* 点击button，变更richText2的Width属性值为$r('app.string.vp_length')
* 获取richText2的Width属性与期待值$r('app.string.vp_length')比对
*/
export default async function richTextWidthTest() {
  defineTest('richTextWidthTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("richTextWidthTestDemo running")
    let driver: Tester = Tester.create()
    let richText1: Component = await driver.findComponent(Matcher.create().id('richTextWidth1').enabled(true))
    let richText2: Component = await driver.findComponent(Matcher.create().id('richTextWidth2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('RichTextWidth').enabled(true))

    let richTextWidth1: string = await richText1.getInspectorInfo()
    assertEqual(JSON.parse(richTextWidth1).$attrs.width, '500.00vp')
    let richTextWidth2: string = await richText2.getInspectorInfo()
    assertEqual(JSON.parse(richTextWidth2).$attrs.width, '100.00px')

    await button.tap()
    let richTextWidth3: string = await richText2.getInspectorInfo()
    assertEqual(JSON.parse(richTextWidth3).$attrs.width, $r('app.string.vp_length'))
  }, 0)
}