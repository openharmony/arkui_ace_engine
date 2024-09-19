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
* RichText组件 layoutWeight属性
* 找到画面id为richTextLayoutWeight的RichText组件
* 找到画面文本为RichTextLayoutWeight的Button组件
* 获取richText的layoutWeight属性与期待值'100px'比对
* 点击button，变更richText的layoutWeight属性值为1
* 获取richText的layoutWeight属性与期待值1比对
*/
export default async function richTextLayoutWeightTest() {
  defineTest('richTextLayoutWeightTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("richTextLayoutWeightTestDemo running")
    let driver: Tester = Tester.create()
    let richText: Component = await driver.findComponent(Matcher.create().id('richTextLayoutWeight').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('RichLayoutWeightType').enabled(true))

    let richTextLayoutWeight1: string = await richText.getInspectorInfo()
    assertEqual(JSON.parse(richTextLayoutWeight1).$attrs.layoutWeight, '100px')

    await button.tap()
    let richTextLayoutWeight2: string = await richText.getInspectorInfo()
    assertEqual(JSON.parse(richTextLayoutWeight2).$attrs.layoutWeight, 1)
  }, 0)
}