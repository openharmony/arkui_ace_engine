#!/usr/bin/env python
# -*- coding: utf-8 -*-
# Copyright (c) 2024 Huawei Device Co., Ltd.
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

import re
import sys


def main(input_path, output_path):
    with open(output_path, "w", encoding="utf-8") as ohos:
        export_content = "export default { "
        with open(input_path, "r", encoding="utf-8") as f:
            line = f.readline()
            isFirstClass = True
            class_num = 0
            while (line):
                ohos.write(line)
                if (line.startswith("class ")):
                    class_num += 1
                    if class_num % 5 == 0:
                        class_num = 0
                        isFirstClass = True
                        export_content += ",\n\t"

                    class_name = re.match(r"class\s+(\w+)", line).group(1)
                    if isFirstClass:
                        isFirstClass = False
                    else:
                        export_content += ", "
                    export_content += class_name
                line = f.readline()
            ohos.write("\n")
        export_content += " };\n"
        export_content += "globalThis.__getUIContext__ = __getUIContext__;\n"
        export_content += "globalThis.__getFrameNodeByNodeId__ = __getFrameNodeByNodeId__;\n"
        export_content += "globalThis.__checkRegexValid__ = __checkRegexValid__;"
        ohos.write("\n" + export_content)


if __name__ == "__main__":
    main(sys.argv[1], sys.argv[2])
