/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

const hilog = requireNapi('hilog');
const Want = requireNapi('app.ability.Want');
const emitter = requireNapi('events.emitter');

const tag = 'AddFormMenuItem::js::';
const ERR_DEVICE_NOT_SUPPORTED = 801;

/**
 * Build function of AddFormMenuItem.
 *
 * @param { Want } want - The want of the form to publish.
 * @param { string } componentId - The id of the component used to get form snapshot.
 * @param { AddFormOptions } [options] - Add form options.
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 12
 */
export function AddFormMenuItem(want, componentId, options, parent = null) {
  hilog.error(0x3900, tag, 'Form menu not supported.');
  emitter.emit({eventId: ERR_DEVICE_NOT_SUPPORTED});
}

export default { AddFormMenuItem };
