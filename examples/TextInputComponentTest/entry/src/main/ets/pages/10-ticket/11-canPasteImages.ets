/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the 'License');
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an 'AS IS' BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import image from '@ohos.multimedia.image';

@Entry
@Component
struct CanPasteImages {
  style: MutableStyledString = new MutableStyledString('');
  textController: TextController = new TextController();
  imagePixelMap: image.PixelMap | undefined = undefined;

  async aboutToAppear() {
    this.imagePixelMap = await this.getPixmapFromMedia($r('app.media.startIcon'));
  }

  private async getPixmapFromMedia(resource: Resource) {
    let unit8Array = await getContext(this)?.resourceManager?.getMediaContent({
      bundleName: resource.bundleName,
      moduleName: resource.moduleName,
      id: resource.id
    });
    let imageSource = image.createImageSource(unit8Array.buffer.slice(0, unit8Array.buffer.byteLength));
    let createPixelMap: image.PixelMap = await imageSource.createPixelMap({
      desiredPixelFormat: image.PixelMapFormat.RGBA_8888,
      desiredSize: { width: 50, height: 50 }
    });
    await imageSource.release();
    return createPixelMap;
  }

  build() {
    Column() {
      Text('==========操作==========\n' +
        '1、点击【添加图片】3次，全选图片并复制。\n' +
        '2、粘贴图片到TextInput、TextArea、Search。\n' +
        '==========期望==========\n' +
        'TextInput、TextArea、Search的内容为3个空格。')

      TextInput({ placeholder: 'TextInput' })
      TextArea({ placeholder: 'TextArea' })
      Search({ placeholder: 'Search' })

      Text(undefined, { controller: this.textController })
        .copyOption(CopyOptions.InApp)
        .fontSize(30)

      Button('添加图片')
        .onClick(() => {
          if (this.imagePixelMap !== undefined) {
            this.style.appendStyledString(new MutableStyledString(new ImageAttachment({
              value: this.imagePixelMap,
              size: { width: 50, height: 50 },
              verticalAlign: ImageSpanAlignment.BASELINE,
              objectFit: ImageFit.Contain
            })))
            this.textController.setStyledString(this.style)
          }
        })

    }

  }
}