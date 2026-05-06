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


EXTRA_EXPORTS = [
    "SmartGestureAction",
    "OperateIntention",
    "BaseGestureHandlingProposal",
    "TargetedGestureProposal",
    "ClickActionProposal",
    "SelectActionProposal",
    "NoneActionProposal",
    "BackPressActionProposal",
    "PageSwitchActionProposal",
    "ScrollActionProposal",
    "GestureHandlingResolution",
]


def append_export_name(export_state, export_name):
    if export_state["count"] != 0 and export_state["count"] % 5 == 0:
        export_state["content"] += ",\n\t"
        export_state["is_first"] = True
    if export_state["is_first"]:
        export_state["is_first"] = False
    else:
        export_state["content"] += ", "
    export_state["content"] += export_name
    export_state["count"] += 1


def main(input_path, output_path):
    with open(output_path, "w", encoding="utf-8") as ohos:
        export_state = {
            "content": "export default { ",
            "count": 0,
            "is_first": True,
        }
        declared_names = set()
        with open(input_path, "r", encoding="utf-8") as f:
            line = f.readline()
            while (line):
                ohos.write(line)
                if (line.startswith("class ")):
                    class_name = re.match(r"class\s+(\w+)", line).group(1)
                    declared_names.add(class_name)
                    append_export_name(export_state, class_name)
                const_match = re.match(r"const\s+(\w+)\s*=", line)
                if const_match:
                    declared_names.add(const_match.group(1))
                line = f.readline()
            for export_name in EXTRA_EXPORTS:
                if export_name in declared_names:
                    append_export_name(export_state, export_name)
            ohos.write("\n")
        export_content = export_state["content"] + " };\n"
        export_content += "globalThis.__getUIContext__ = __getUIContext__;\n"
        export_content += "globalThis.__getFrameNodeByNodeId__ = __getFrameNodeByNodeId__;\n"
        export_content += "globalThis.__addAvailableInstanceId__ = __addAvailableInstanceId__;\n"
        export_content += "globalThis.__removeAvailableInstanceId__ = __removeAvailableInstanceId__;\n"
        export_content += "globalThis.__checkRegexValid__ = __checkRegexValid__;\n"
        export_content += "globalThis.__getResourceId__ = __getResourceId__;"
        ohos.write("\n" + export_content)


if __name__ == "__main__":
    main(sys.argv[1], sys.argv[2])
