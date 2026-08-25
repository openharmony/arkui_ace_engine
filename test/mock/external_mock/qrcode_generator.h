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

#ifndef TEST_MOCK_EXTERNAL_MOCK_QRCODE_GENERATOR_H
#define TEST_MOCK_EXTERNAL_MOCK_QRCODE_GENERATOR_H

#include <cstdint>

typedef enum {
    QRCODE_ECC_LOW,
    QRCODE_ECC_MEDIUM,
    QRCODE_ECC_QUARTILE,
    QRCODE_ECC_HIGH,
} QRCODE_ECC;

typedef struct QrcodeImage {
    uint32_t width;
    uint8_t* data;
} QrcodeImage;

inline QrcodeImage* QrcodeImageEncodeString(const char*, QRCODE_ECC)
{
    static uint8_t data[] = { 0, 1, 1, 0 };
    static QrcodeImage img = { 2, data };
    return &img;
}

inline void QrcodeImageFree(QrcodeImage*) {}

inline bool QrcodeGetModule(const QrcodeImage*, int, int)
{
    return false;
}

#endif // TEST_MOCK_EXTERNAL_MOCK_QRCODE_GENERATOR_H
