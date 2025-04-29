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
* RichText组件 size属性
* 找到画面id为richTextSize1,richTextSize2的RichText组件
* 找到画面文本为RichTextSize的Button组件
* 获取richText1的size属性与期待值500.00vp比对
* 获取richText2的size属性与期待值'100.00px'比对
* 点击button，变更richText2的size属性值为$r('app.string.vp_length')
* 获取richText2的size属性与期待值$r('app.string.vp_length')比对
*/
export default async function richTextSizeTest() {
  defineTest('richTextSizeTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("richTextSizeTestDemo running")
    let driver: Tester = Tester.create()
    let richText1: Component = await driver.findComponent(Matcher.create().id('richTextSize1').enabled(true))
    let richText2: Component = await driver.findComponent(Matcher.create().id('richTextSize2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('RichTextSize').enabled(true))

    let richTextSize1: string = await richText1.getInspectorInfo()
    assertEqual(JSON.parse(richTextSize1).$attrs.size.width, '500.00vp')
    assertEqual(JSON.parse(richTextSize1).$attrs.size.height, '500.00vp')
    let richTextSize2: string = await richText2.getInspectorInfo()
    assertEqual(JSON.parse(richTextSize2).$attrs.size.width, '100.00px')
    assertEqual(JSON.parse(richTextSize2).$attrs.size.height, '100.00px')

    await button.tap()
    let richTextSize3: string = await richText2.getInspectorInfo()
    assertEqual(JSON.parse(richTextSize3).$attrs.size.width, $r('app.string.vp_length'))
    assertEqual(JSON.parse(richTextSize3).$attrs.size.height, $r('app.string.vp_length'))
  }, 0)
}