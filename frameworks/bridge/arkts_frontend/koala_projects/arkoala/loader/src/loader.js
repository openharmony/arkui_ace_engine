/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

jsModule = require(`./index-node.js`)

function sendClick(control, target, status) {
    control.sendMessage("arkoala.press", {
        kind: 1, /* SinglePointerInput */
        nodeId: target,
        x: 22,
        y: 33,
        status: status
    })
}

function sendText(control, target, status) {
    control.sendMessage("arkoala.text.input", {
        nodeId: target,
        text: "Hello"
    })
}


function registerPage(control, url, page) {
    control.sendMessage("arkoala.router.register", {
        page: page,
        url: url
    })
}

function pushPage(control, url, params) {
    control.sendMessage("arkoala.router.push", {
        url: url,
        params: params
    })
}

function backPage(control, url, params) {
    control.sendMessage("arkoala.router.back", {
        url: url,
        params: params
    })
}

jsModule.startApplication(
    jsModule.getEntry()
).then(control => {
    // Emulate input events.
    sendClick(control, 1023, 0) // pointer down
    sendClick(control, 1024, 0) // pointer down
    sendClick(control, 1023, 1) // pointer up
    sendClick(control, 1024, 1) // pointer up
    setTimeout(() => {
        sendText(control, 1023, "Hello")
        sendClick(control, 1017, 0) // pointer down
    }, 100)
    setTimeout(() => {
        sendClick(control, 1018, 0) // pointer down
    }, 200)
    setTimeout(() => {
        registerPage(control, "page", jsModule.getPage())
        pushPage(control, "page")
        setTimeout(async () => {
            backPage(control, undefined)
            setTimeout(() => process.exit(0), 500)
        }, 1000)
    }, 2000)
})
