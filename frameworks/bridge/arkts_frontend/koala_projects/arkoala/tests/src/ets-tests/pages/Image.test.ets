/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

@Entry
@Component
struct ImageTest {

  build() {
    Text("Image test")
    Image("/path/to/imageSrc") {
    }
    .alt("/altPath/to/imageSrc")
    .matchTextDirection(true)
    .fitOriginalSize(false)
    .fillColor("0xabcdef")
    .objectFit(ImageFit.None)
    .objectRepeat(ImageRepeat.XY)
    .autoResize(true)
    .renderMode(ImageRenderMode.Template)
    .interpolation(ImageInterpolation.High)
    .sourceSize({width: 123.4, height: 567.8})
    .syncLoad(false)
    .copyOption(CopyOptions.CROSS_DEVICE)
    .draggable(true)
    .edgeAntialiasing(1.2)
    .enableAnalyzer(false)
    .analyzerConfig({types: [ImageAnalyzerType.SUBJECT, ImageAnalyzerType.TEXT]})
    .resizable({slice: {left: 1, top: 2, right: 3, bottom: 4}})
    //.colorFilter(new ColorFilter([1, 3, 5]))
  }
    
}