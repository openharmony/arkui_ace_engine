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

const __MovingPhotoView__ = requireInternal("multimedia.movingphotoview");
var PixelMapFormat;
(function (PixelMapFormat) {
    PixelMapFormat[PixelMapFormat["RGBA_8888"] = 0] = "RGBA_8888";
    PixelMapFormat[PixelMapFormat["NV21"] = 1] = "NV21";
})(PixelMapFormat || (PixelMapFormat = {}));

class MovingPhotoView extends JSViewAbstract {
    static create(value) {
        __MovingPhotoView__.create(value);
    }

    static muted(value) {
        __MovingPhotoView__.muted(value);
    }

    static objectFit(value) {
        __MovingPhotoView__.objectFit(value);
    }

    static onComplete(value) {
        __MovingPhotoView__.onComplete(value);
    }

    static onStart(value) {
        __MovingPhotoView__.onStart(value);
    }

    static onStop(value) {
        __MovingPhotoView__.onStop(value);
    }

    static onPause(value) {
        __MovingPhotoView__.onPause(value);
    }

    static onFinish(value) {
        __MovingPhotoView__.onFinish(value);
    }

    static onError(value) {
        __MovingPhotoView__.onError(value);
    }

    static onClick(value) {
        __Common__.onClick(value);
    }

    static onAppear(value) {
        __Common__.onAppear(value);
    }

    static onDisAppear(value) {
        __Common__.onDisAppear(value);
    }

    static onTouch(value) {
        __Common__.onTouch(value);
    }

    static onHover(value) {
        __Common__.onHover(value);
    }

    static onKeyEvent(value) {
        __Common__.onKeyEvent(value);
    }

    static onDeleteEvent(value) {
        __Common__.onDeleteEvent(value);
    }

    static remoteMessage(value) {
        __Common__.remoteMessage(value);
    }

    static autoPlayPeriod(startTime, endTime) {
        __MovingPhotoView__.autoPlayPeriod(startTime, endTime);
    }

    static autoPlay(value) {
        __MovingPhotoView__.autoPlay(value);
    }

    static repeatPlay(value) {
        __MovingPhotoView__.repeatPlay(value);
    }
    
    static enableAnalyzer(value) {
        __MovingPhotoView__.enableAnalyzer(value);
    }
}

export default {
    MovingPhotoView,
    MovingPhotoViewController: __MovingPhotoView__.MovingPhotoViewController,
    PixelMapFormat,
};
