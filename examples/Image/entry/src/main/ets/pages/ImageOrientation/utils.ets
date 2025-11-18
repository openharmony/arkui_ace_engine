/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
export function convertOrientationToString(orientation: ImageRotateOrientation): string | undefined {
  switch (orientation) {
    case ImageRotateOrientation.UP:
      return "UP"
    case ImageRotateOrientation.DOWN:
      return "DOWN"
    case ImageRotateOrientation.LEFT:
      return "LEFT"
    case ImageRotateOrientation.RIGHT:
      return "RIGHT"
    case ImageRotateOrientation.AUTO:
      return "AUTO"
    default:
      return undefined
  }
}

export function convertRepeatToString(orientation: ImageRepeat): string | undefined {
  switch (orientation) {
    case ImageRepeat.NoRepeat:
      return "NoRepeat"
    case ImageRepeat.X:
      return "X"
    case ImageRepeat.Y:
      return "Y"
    case ImageRepeat.XY:
      return "XY"
    default:
      return undefined
  }
}

export function convertImageFitToString(fit: ImageFit): string | undefined {
  switch (fit) {
    case ImageFit.Contain:
      return "Contain"
    case ImageFit.Cover:
      return "Cover"
    case ImageFit.Auto:
      return "Auto"
    case ImageFit.Fill:
      return "Fill"
    case ImageFit.ScaleDown:
      return "ScaleDown"
    case ImageFit.None:
      return "None"
    case ImageFit.TOP_START:
      return "TOP_START"
    case ImageFit.TOP:
      return "TOP"
    case ImageFit.TOP_END:
      return "TOP_END"
    case ImageFit.START:
      return "START"
    case ImageFit.CENTER:
      return "CENTER"
    case ImageFit.END:
      return "END"
    case ImageFit.BOTTOM_START:
      return "BOTTOM_START"
    case ImageFit.BOTTOM:
      return "BOTTOM"
    case ImageFit.BOTTOM_END:
      return "BOTTOM_END"
    default:
      return undefined
  }
}
