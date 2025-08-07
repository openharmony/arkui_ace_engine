/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

/**
 * 下载与显示网络gif图片
 */
import { cacheDownload } from '@kit.BasicServicesKit';

@Entry
@Component
struct Index {
  @State src: string = 'xxx.gif'; // 请填写一个具体的网络图片地址。

  async aboutToAppear(): Promise<void> {
    // 提供缓存下载任务的配置选项。
    let options: cacheDownload.CacheDownloadOptions = {};
    try {
      // 进行缓存下载，资源若下载成功会被缓存到应用内存或应用沙箱目录的特定文件中。
      cacheDownload.download(this.src, options);
      console.error(`successs to download the resource. `);
    } catch (err) {
      console.error(`Failed to download the resource. err: ${JSON.stringify(err)}`);
    }
  }

  build() {
    Column() {
      // 若src指定的是网络图片且已成功下载并缓存，则本次显示无需重复下载。
      Image(this.src)
        .width(100)
        .height(100)
        .objectFit(ImageFit.Cover)
        .borderWidth(1)
    }
    .height('100%')
    .width('100%')
  }
}