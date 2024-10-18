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
import {
  assertEqual,
  assertFalse,
  assertTrue,
  Component,
  defineTest,
  Matcher,
  TestCaseLevel,
  Tester
} from '@ohos.arkui.componentTest'

export default async function imageAltTest() {
  /*
* Image组件 Alt属性
* 找到画面id为imageAlt1,imageAlt2的Image组件
* 找到画面文本为ImageAlt1,ImageAlt2的Button组件
* 获取image1的Alt属性与期待值$r('app.media.run_icon')比对
* 获取image2的Alt属性与期待值"pages/image/image_two.png"比对
* 点击button1，变更image1的Alt属性值为"pages/image/image_one.png"
* 获取image1的Alt属性与期待值"pages/image/image_one.png"比对
* 点击button2，变更image2的Alt属性值为$r('app.media.run_icon')
* 获取image2的Alt属性与期待值$r('app.media.run_icon')比对
*/
  defineTest('imageAltTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("imageAltTestDemo running")
    let driver: Tester = Tester.create()
    let image1: Component = await driver.findComponent(Matcher.create().id('imageAlt1').enabled(true))
    let image2: Component = await driver.findComponent(Matcher.create().id('imageAlt2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ImageAlt1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('ImageAlt2').enabled(true))
    let alt1: string = await image1.getInspectorInfo()
    assertEqual(JSON.parse(alt1).$attrs.alt, $r('app.media.city_icon'))
    await button1.tap()
    let alt2: string = await image1.getInspectorInfo()
    assertEqual(JSON.parse(alt2).$attrs.alt, "pages/image/image_two.png")
    let alt3: string = await image2.getInspectorInfo()
    assertEqual(JSON.parse(alt3).$attrs.alt, "pages/image/image_one.png")
    await button2.tap()
    let alt4: string = await image2.getInspectorInfo()
    assertEqual(JSON.parse(alt4).$attrs.alt, $r('app.media.run_icon'))
  }, 0)
}