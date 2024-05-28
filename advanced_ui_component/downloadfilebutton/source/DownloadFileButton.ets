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

export enum DownloadIconStyle {
  FULL_FILLED = 1,
  LINES = 2
}

export enum DownloadDescription {
  DOWNLOAD = 1,
  DOWNLOAD_FILE = 2,
  SAVE = 3,
  SAVE_IMAGE = 4,
  SAVE_FILE = 5,
  DOWNLOAD_AND_SHARE = 6,
  RECEIVE = 7,
  CONTINUE_TO_RECEIVE = 8
}

export enum DownloadLayoutDirection {
  HORIZONTAL = 0,
  VERTICAL = 1
}

const downloadDescriptionResourceMap = new Map([
  [DownloadDescription.DOWNLOAD, $r('sys.string.ohos_id_text_save_button_description_download')],
  [DownloadDescription.DOWNLOAD_FILE, $r('sys.string.ohos_id_text_save_button_description_download_file')],
  [DownloadDescription.SAVE, $r('sys.string.ohos_id_text_save_button_description_save')],
  [DownloadDescription.SAVE_IMAGE, $r('sys.string.ohos_id_text_save_button_description_save_image')],
  [DownloadDescription.SAVE_FILE, $r('sys.string.ohos_id_text_save_button_description_save_file')],
  [DownloadDescription.DOWNLOAD_AND_SHARE, $r('sys.string.ohos_id_text_save_button_description_download_and_share')],
  [DownloadDescription.RECEIVE, $r('sys.string.ohos_id_text_save_button_description_receive')],
  [DownloadDescription.CONTINUE_TO_RECEIVE, $r('sys.string.ohos_id_text_save_button_description_continue_to_receive')]
]);

export interface DownloadContentOptions {
  icon?: DownloadIconStyle;
  text?: DownloadDescription;
}

export interface DownloadStyleOptions {
  iconSize?: Dimension;
  layoutDirection?: DownloadLayoutDirection;
  fontSize?: Dimension;
  fontStyle?: FontStyle;
  fontWeight?: number | FontWeight | string;
  fontFamily?: string | Resource;
  fontColor?: ResourceColor;
  iconColor?: ResourceColor;
  textIconSpace?: Dimension;
}

const MARGIN_DEFAULT = '0vp';

@Component
export struct DownloadFileButton {
  @State contentOptions: DownloadContentOptions = {
    icon: DownloadIconStyle.FULL_FILLED,
    text: DownloadDescription.DOWNLOAD
  };
  @State styleOptions: DownloadStyleOptions = {
    iconSize: '16vp',
    layoutDirection: DownloadLayoutDirection.HORIZONTAL,
    fontSize: '16fp',
    fontStyle: FontStyle.Normal,
    fontWeight: FontWeight.Medium,
    fontFamily: 'HarmonyOS Sans',
    fontColor: '#ffffffff',
    iconColor: '#ffffffff',
    textIconSpace: '4vp'
  };

  private getTextContent(description: DownloadDescription): Resource | undefined {
    return downloadDescriptionResourceMap.get(description);
  }

  @Builder
  downloadImage() {
    Image(
      this.contentOptions.icon === DownloadIconStyle.LINES ?
      $r('sys.media.ohos_save_button_line') :
      $r('sys.media.ohos_save_button_filled')
    )
      .size({ width: this.styleOptions.iconSize, height: this.styleOptions.iconSize })
      .fillColor(this.styleOptions.iconColor)
  }

  @Builder
  downloadText() {
    Text(
      !this.contentOptions.text || !this.getTextContent(this.contentOptions.text) ?
      $r('sys.string.ohos_id_text_save_button_description_download') :
      this.getTextContent(this.contentOptions.text)
    )
      .fontSize(this.styleOptions.fontSize)
      .fontColor(this.styleOptions.fontColor)
      .fontStyle(this.styleOptions.fontStyle)
      .fontWeight(this.styleOptions.fontWeight)
      .fontFamily(this.styleOptions.fontFamily)
      .margin({
        top: this.styleOptions.layoutDirection === DownloadLayoutDirection.VERTICAL ?
        this.styleOptions.textIconSpace :
          MARGIN_DEFAULT,
        left: this.styleOptions.layoutDirection === DownloadLayoutDirection.HORIZONTAL ?
        this.styleOptions.textIconSpace :
          MARGIN_DEFAULT
      })
  }

  build() {
    if (this.styleOptions.layoutDirection === DownloadLayoutDirection.HORIZONTAL) {
      Row() {
        if (this.contentOptions.icon) {
          this.downloadImage()
        }
        if (this.contentOptions.text) {
          this.downloadText()
        }
      }
    } else {
      Column() {
        if (this.contentOptions.icon) {
          this.downloadImage()
        }
        if (this.contentOptions.text) {
          this.downloadText()
        }
      }
    }
  }
}
