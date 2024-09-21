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
import { assertEqual, Component, defineTest, Matcher, TestCaseLevel, Tester } from '@ohos.arkui.componentTest'


export default async function progressBackgroundColorTest() {
  /*
* Progress组件 BackgroundColor属性
* 找到画面id为progressBackgroundColor1,progressBackgroundColor2的Progress组件
* 找到画面文本为ProgressBackgroundColor1,ProgressBackgroundColor2组件
* 获取progress1的BackgroundColor属性与期待值Color.Red比对
* 获取progress1的BackgroundColor属性与期待值$r("app.color.progress_background_color")比对
* 点击button1，变更progress1的BackgroundColor属性值为0x000000
* 获取image1的BackgroundColor属性与期待值0x000000比对
* 点击button2，变更progress1的BackgroundColor属性值为'#0000ff'
* 获取image2的BackgroundColor属性与期待值'#0000ff'比对
*/
  defineTest('progressBackgroundColorTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("progressBackgroundColorTestDemo running")
    let driver: Tester = Tester.create()
    let progress1: Component = await driver.findComponent(Matcher.create().id('progressBackgroundColor1').enabled(true))
    let progress2: Component = await driver.findComponent(Matcher.create().id('progressBackgroundColor2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ProgressBackgroundColor1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('ProgressBackgroundColor2').enabled(true))
    let backgroundColor1: string = await progress1.getInspectorInfo()
    assertEqual(JSON.parse(backgroundColor1).$attrs.backgroundColor.toLowerCase(), Color.Red)
    let backgroundColor2: string = await progress2.getInspectorInfo()
    assertEqual(JSON.parse(backgroundColor2).$attrs.backgroundColor, $r("app.color.progress_background_color"))
    await button1.tap()
    let backgroundColor3: string = await progress1.getInspectorInfo()
    assertEqual(JSON.parse(backgroundColor3).$attrs.backgroundColor, '#FF000000')
    await button2.tap()
    let backgroundColor4: string = await progress1.getInspectorInfo()
    assertEqual(JSON.parse(backgroundColor4).$attrs.backgroundColor, '#FF0000FF')
  }, 0)
}