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

let Max: number = 4000
let i: number = 0
let end: number = 0
let segment: string = ''

export default async function navigationBackButtonIconTest() {
  /*
* Navigation组件 BackButtonIcon属性
* 找到画面id为navigationBackButtonIcon的Navigation组件
* 找到画面文本为NavigationBackButtonIcon1、 NavigationBackButtonIcon2的Button组件
* 获取navigation1的BackButtonIcon属性与期待值"../../../resources/base/media/test_image.png"比对
* 点击button1，变更navigation1的BackButtonIcon属性值为$r('sys.media.ohos_ic_public_phone')
* 获取navigation1的BackButtonIcon属性与期待值$r('sys.media.ohos_ic_public_phone')比对
* 点击button2，变更navigation1的BackButtonIcon属性值为srcPixelMap
* 获取navigation1的BackButtonIcon属性与期待值'srcPixelMap'比对
*/
  defineTest('navigationBackButtonIconTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("navigationBackButtonIconTestDemo running")
    let driver: Tester = Tester.create()
    let navigation1: Component =
      await driver.findComponent(Matcher.create().id('navigationBackButtonIcon').enabled(true))
    let button1: Component =
      await driver.findComponent(Matcher.create().text('NavigationBackButtonIcon1').enabled(true))
    let button2: Component =
      await driver.findComponent(Matcher.create().text('NavigationBackButtonIcon2').enabled(true))
    let backButton1: string = await navigation1.getInspectorInfo()
    assertEqual(JSON.parse(backButton1).$attrs.backButtonIcon, "../../../resources/base/media/test_image.png")
    await button1.tap()
    let backButton2: string = await navigation1.getInspectorInfo()
    assertEqual(JSON.parse(backButton2).$attrs.backButtonIcon, $r('sys.media.ohos_ic_public_phone'))
    await button2.tap()
    let backButton3: string = await navigation1.getInspectorInfo()
    assertEqual(JSON.parse(backButton3).$attrs.backButtonIcon, 'srcPixelMap')
  }, 0)
}