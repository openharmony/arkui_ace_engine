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

export default async function textTextOverflowTest() {
  /*
* Text组件 TextOverflow属性
* 找到画面id为textTextOverflow1,textTextOverflow2，textTextOverflow3的Text组件
* 找到画面文本为TextTextOverflow的Button组件
* 获取text1的TextOverflow属性与期待值TextOverflow.None比对
* 获取text2的TextOverflow属性与期待值TextOverflow.Clip比对
* 获取text3的TextOverflow属性与期待值TextOverflow.Ellipsis比对
* 点击button，变更text3的TextOverflow属性值为TextOverflow.MARQUEE
* 获取text3的TextOverflow属性与期待值TextOverflow.MARQUEE比对
*/
  defineTest('textTextOverflowTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("textTextOverflowTestDemo running")
    let driver: Tester = Tester.create()
    let text1: Component = await driver.findComponent(Matcher.create().id('textTextOverflow1').enabled(true))
    let text2: Component = await driver.findComponent(Matcher.create().id('textTextOverflow2').enabled(true))
    let text3: Component = await driver.findComponent(Matcher.create().id('textTextOverflow3').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('TextTextOverflow').enabled(true))

    let textOverflow1: string = await text1.getInspectorInfo()
    assertEqual(JSON.parse(textOverflow1).$attrs.textOverflow, 'TextOverflow.None')
    let textOverflow2: string = await text2.getInspectorInfo()
    assertEqual(JSON.parse(textOverflow2).$attrs.textOverflow, 'TextOverflow.Clip')
    let textOverflow3: string = await text3.getInspectorInfo()
    assertEqual(JSON.parse(textOverflow3).$attrs.textOverflow, 'TextOverflow.Ellipsis')

    await button.tap()
    let textOverflow4: string = await text3.getInspectorInfo()
    assertEqual(JSON.parse(textOverflow4).$attrs.textAlign, 'TextOverflow.MARQUEE')
  }, 0)
}