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

export default async function imageAnimatorImagesTest() {
  /*
* ImageAnimator组件 Images属性
* 找到画面id为imageAnimatorImages的ImageAnimator组件
* 找到画面文本为ImageAnimatorImageFrameInfo的Button组件
* 获取imageAnimator的images属性与期待值[{"src":"pages/imageAnimator/imageAnimator_one.png","left":"10.00px","top":"10.00px",
* "width":"200.00px","height":"200.00px","duration":"2000"}]比对
* 点击button1，变更imageAnimator的images.src属性值为$r('app.media.city_icon'),images.width属性值为400,images.height的属性值为200
* images.top的属性值为10,images.left的属性值为10,images.duration的属性值为2000
* 获取imageAnimator的images属性与期待值[{"src":"file://F:\\arkui_componenttest\\test\\componenttest\\testcase\\components\\image_video_and_media\\
* entry\\src\\main\\resources\\base\\media\\city_icon.png","left":"10.00vp","top":"10.00vp","width":"400.00vp",
* "height":"200.00vp","duration":"2000"}]比对
*/
  defineTest('imageAnimatorImagesTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("imageAnimatorImagesTestDemo running")
    let driver: Tester = Tester.create()
    let imageAnimator: Component = await driver.findComponent(Matcher.create().id('imageAnimatorImages').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ImageAnimatorImages').enabled(true))
    let images1: string = await imageAnimator.getInspectorInfo()
    assertEqual(JSON.parse(images1).$attrs.images,
      '[{"src":"pages/imageAnimator/imageAnimator_one.png","left":"10.00px","top":"10.00px","width":"200.00px","height":"200.00px","duration":"2000"}]')

    await button1.tap()
    let images2: string = await imageAnimator.getInspectorInfo()
    assertEqual(JSON.parse(images2).$attrs.images,
      '[{"src":"file://F:\\arkui_componenttest\\test\\componenttest\\testcase\\components\\image_video_and_media\\entry\\src\\main\\resources\\base\\media\\city_icon.png","left":"10.00vp","top":"10.00vp","width":"400.00vp","height":"200.00vp","duration":"2000"}]')
  }, 0)
}