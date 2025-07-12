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

// TODO: remove private export
export * from "./utilities/private"
export * from "./utilities/public"
export * from "./types"
export * from "./factory/nodeFactory"
export * from "./factory/nodeTests"
export {
    visitEachChild,
} from "./visitor/visitor"
export {
    SyntaxKind,
    NodeFlags,
} from "./static/enums"

// from ArkTS api
export * from "../arkts-api/static/global"
export {
    Es2pandaContextState as ContextState,
    Es2pandaPrimitiveType as Es2pandaPrimitiveType,
} from "../arkts-api"
