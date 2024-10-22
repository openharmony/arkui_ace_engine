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

const __ArcSwiper__ = requireInternal("arkui.ArcSwiper");

class ArcSwiper extends JSViewAbstract {
    static create(value) {
        __ArcSwiper__.create(value);
    }

    static index(value) {
        __ArcSwiper__.index(value);
    }

    static indicator(value) {
        __ArcSwiper__.indicator(value);
    }

    static duration(value) {
        __ArcSwiper__.duration(value);
    }

    static vertical(value) {
        __ArcSwiper__.vertical(value);
    }

    static disableSwipe(value) {
        __ArcSwiper__.disableSwipe(value);
    }

    static onChange(value) {
        __ArcSwiper__.onChange(value);
    }

    static onAnimationStart(value) {
        __ArcSwiper__.onAnimationStart(value);
    }

    static onAnimationEnd(value) {
        __ArcSwiper__.onAnimationEnd(value);
    }

    static onGestureSwipe(value) {
        __ArcSwiper__.onGestureSwipe(value);
    }

    static digitalCrownSensitivity(value) {
        __ArcSwiper__.digitalCrownSensitivity(value);
    }

    static effectMode(value) {
        __ArcSwiper__.effectMode(value);
    }

    static customContentTransition(value) {
        __ArcSwiper__.customContentTransition(value);
    }

    static disableTransitionAnimation(value) {
        __ArcSwiper__.disableTransitionAnimation(value);
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
}

export default {
    ArcSwiper,
    ArcSwiperController: __ArcSwiper__.ArcSwiperController,
    ArcDotIndicator: __ArcSwiper__.ArcDotIndicator,
    ArcDirection: __ArcSwiper__.ArcDirection,
};
