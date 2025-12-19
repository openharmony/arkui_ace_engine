#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# Copyright (c) 2025 Huawei Device Co., Ltd.
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import os
from datetime import datetime

COPY_RIGHT_HEADER = '''/*
 * Copyright (c) %s Huawei Device Co., Ltd.
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
 */\n
''' % (datetime.now().year)

def prepend_header_to_files():
    for dirpath, _, filenames in os.walk(os.getcwd()):
        for filename in filenames:
            if filename.endswith(('.js', '.ets')):
                file_path = os.path.join(dirpath, filename)
                with open(file_path, 'r', encoding = 'utf-8') as file:
                    content = file.read()
                new_content = COPY_RIGHT_HEADER + content
                with open(file_path, 'w', encoding = 'utf-8') as file:
                    file.write(new_content)

if __name__ == "__main__":
    prepend_header_to_files()