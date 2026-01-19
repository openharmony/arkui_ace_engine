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
 * 
 * BusinessError & errorCode
 * 
 */
class BusinessError extends Error {	 
    code: number | string;	 
    constructor(code: number | string, message: string) {	 
        super(message);	 
        this.code = code;	 
        this.name = 'BusinessError';	 
    }	 
}	 
// addMonitor
const ADD_MONITOR_FAIL_TARGET_ILLEGAL: string = '130000';	 
const ADD_MONITOR_FAIL_PATH_ILLEGAL: string = '130001';	 
const ADD_MONITOR_FAIL_FUNC_ILLEGAL: string = '130002';
// SyncMonitor 
const SYNC_MONITOR_FAIL_PATH_ILLEGAL: number = 130001; 
// applySync/flushUpdates/flushUIUpdates
const FUNC_CALLED_IN_COMPUTED_ILLEGAL: number = 140001;	 
const FUNC_CALLED_IN_MONITOR_ILLEGAL: number = 140002;
// @Builder
const INVALID_SET_IN_BUILDER: number = 140109;
// @Track
const NON_TRACK_PROPERTY_ON_UI: number = 140110;
// interop
const STATIC_VARIABLE_TO_PROP: number = 140111;
// PersistenceV2
const PERSISTENCE_V2_NOT_SUPPORT_AREA_MODE_MESSAGE: number = 140106;
const PERSISTENCE_V2_KEYS_DUPLICATE: number = 140105;
const PERSISTENCE_V2_MISMATCH_BETWEEN_KEY_AND_TYPE: number = 140107;
const PERSISTENCE_V2_LACK_TYPE: number = 140108;
// PersistenceV2/AppStorageV2
const PERSISTENCE_V2_APPSTORAGE_V2_UNSUPPORTED_TYPE: number = 140103;
const PERSISTENCE_V2_APPSTORAGE_V2_INVALID_DEFAULT_CREATOR: number = 140104;
const PERSISTENCE_V2_APPSTORAGE_V2_INVALID_KEY: number = 140123;
// @Consumer/@Consume
const MISSING_PROVIDE_DEFAULT_VALUE_FOR_CONSUME_CONSUMER: number = 140112;
// @ReusableV2
const REUSABLE_V2_OLD_TOOLCHAIN: number = 140113;
const USE_REUSABLE_V2_IN_COMPONENT: number = 140124;
// @Provide
const DUPLICATE_PROVIDE_KEY: number = 140114;
// @State and V1 state decorator
const ILLEGAL_TYPE_FOR_V1_STATE_VALUE: number = 140115;
// v1v2mix
const USE_TRACK_IN_OBSERVEDV2: number = 140116;
const USE_TRACE_IN_OBSERVED: number = 140117;
const USE_V1_STATE_IN_COMPONENTV2: number = 140118;
const INVALID_INPUT_IN_COMPONENTV2: number = 140119;
// @Env
const ENV_USED_NOT_IN_COMPONENT: number = 140120;
const ENV_READ_ONLY: number = 140122;
const REQUIRE_INTERNAL_ERROR: number = 140121;
const UNSUPPORTED_KEY_IN_ENV: number = 140000;
// unimplemented
const NOT_IMPLEMENT: number = 100201;