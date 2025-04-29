/*
 * Copyright (C) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

module.exports = {
    getDateTime,
    getRunTime
}

function getDateTime() {
    const date = new Date();
    let year = date.getFullYear().toString();
    let month = ("0" + (date.getMonth() + 1)).slice(-2);
    let day = ("0" + date.getDate()).slice(-2);
    let hour = ("0" + date.getHours()).slice(-2);
    let minute = ("0" + date.getMinutes()).slice(-2);
    let second = ("0" + date.getSeconds()).slice(-2);
    let millSecond = ("0" + date.getMilliseconds()).slice(-3);
    return year + month + day + hour + minute + second + millSecond;
}
function getRunTime(startTime) {
    let endTime = new Date().getTime();
    let duration = endTime - startTime;
    let hours = Math.floor(duration / (1000 * 60 * 60));
    let minutes = Math.floor((duration % (1000 * 60 * 60)) / (1000 * 60));
    let seconds = Math.floor((duration % (1000 * 60)) / 1000);
    let formattedTime = `${hours}小时${minutes}分钟${seconds}秒`;
    return formattedTime;
}
