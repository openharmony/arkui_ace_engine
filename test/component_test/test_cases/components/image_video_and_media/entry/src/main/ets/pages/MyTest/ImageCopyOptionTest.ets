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

export default async function imageCopyOptionTest() {
  /*
* Image组件 CopyOption属性
* 找到画面id为imageCopyOption1,imageCopyOption2,imageCopyOption3的Image组件
* 找到画面文本为ImageCopyOption1的Button组件
* 获取image1的CopyOptions属性与期待值CopyOptions.None比对
* 获取image2的CopyOptions属性与期待值CopyOptions.LocalDevice比对
* 获取image3的CopyOptions属性与期待值CopyOptions.CROSS_DEVICE比对
* 点击button1，变更image1的CopyOptions属性值为CopyOptions.InApp
* 获取image1的CopyOptions属性与期待值CopyOptions.InApp比对
*/
  defineTest('imageCopyOptionTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("imageCopyOptionTestDemo running")
    let driver: Tester = Tester.create()
    let image1: Component = await driver.findComponent(Matcher.create().id('imageCopyOption1').enabled(true))
    let image2: Component = await driver.findComponent(Matcher.create().id('imageCopyOption2').enabled(true))
    let image3: Component = await driver.findComponent(Matcher.create().id('imageCopyOption3').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ImageCopyOption1').enabled(true))
    let copyOptions1: string = await image1.getInspectorInfo()
    assertEqual(JSON.parse(copyOptions1).$attrs.copyOption, 'CopyOptions.None')
    let copyOptions2: string = await image2.getInspectorInfo()
    assertEqual(JSON.parse(copyOptions2).$attrs.copyOption, 'CopyOptions.Local')
    let copyOptions3: string = await image3.getInspectorInfo()
    assertEqual(JSON.parse(copyOptions3).$attrs.copyOption, 'CopyOptions.Distributed')
    await button1.tap()
    let copyOptions4: string = await image1.getInspectorInfo()
    assertEqual(JSON.parse(copyOptions4).$attrs.copyOption, 'CopyOptions.InApp')
  }, 0)
}